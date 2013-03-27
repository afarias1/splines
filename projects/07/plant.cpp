#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "plant.h"
#include "parser.h"

using cs40::Plant;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

void Plant::parseFile(QString fname){
    string name = fname.toStdString();
    ifstream infile;
    infile.open(name.c_str());

    if(!infile.good()){
        cout << "error opening file " << name << endl;
        return;
    }

    string line; //current line
    QString lhs;
    float weight;
    unsigned int i;
    vector<string> words;

    m_start_symbol = "";
    while(!infile.eof()){
        getline(infile, line);
        //cout << line <<  endl;
        words = split(line);
        if(words.size()>0){
            if(m_start_symbol == ""){
                m_start_symbol = words[0].c_str();
                //cout << "Read start symbol " << m_start_symbol.toStdString() << endl;
            }
            else {
                lhs = words[0].c_str();
                i=1;
                try{
                    weight = parseFloat(words[1]);
                    i++;
                }
                catch(parser_error e){
                    weight = 1.0;
                }
                Production prod;
                prod.lhs = lhs;
                prod.weight = weight;
                for(; i<words.size(); i++){
                    prod.symbols.push_back(words[i].c_str());
                }
                if(!m_rules.contains(lhs)){
                    m_rules[lhs]=QList<Production>();
                }
                m_rules[lhs].push_back(prod);
            }
        }
    }

    infile.close();
}


/* print grammar rules */
void Plant::printGrammar(){
    cout << "Start Symbol: " << m_start_symbol.toStdString() << endl;
    QHashIterator<QString, QList<Production> > it(m_rules);
     while (it.hasNext()) {
         it.next();
         string lhs = it.key().toStdString();
         QList<Production> prods = it.value();
         for(unsigned int i =0; i<prods.size(); i++){
             cout << lhs << "-> (weight: ";
             cout << prods[i].weight << ") ";
             for(unsigned int j=0; j<prods[i].symbols.size(); j++){
                 cout << prods[i].symbols[j].toStdString() << " ";
             }
             cout << endl;
         }
     }

}

/* derive production from grammar, making depth passes */
QList<QString> Plant::derive(int depth){
    QList<QString> now;
    QList<QString> next;
    now.push_back(m_start_symbol);

    while(depth > 0){
        //TODO: build next iteration using now iteration
        //and rules map

        //copy next over to now
        now = next;
        next.clear();
        depth--;
    }
    return now;
}

