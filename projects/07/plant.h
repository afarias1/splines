#ifndef CS40_PLANT_H
#define CS40_PLANT_H

#include <QHash>
#include <QString>
#include "production.h"


namespace cs40{
	class Plant{
		public:
			Plant(){ /* default constructor */ };
			~Plant(){ /* do nothing ? */ };

			/* parse an input file given by a filename and build the plant grammar from the parsed input */
			void parseFile(QString fname);
			/* print grammar rules */
			void printGrammar();

			/* derive production from grammar, making depth passes */
			QList<QString> derive(int depth);

		protected:
			QHash<QString, QList<cs40::Production> > m_rules;
			QString m_start_symbol;
	};
}

#endif
