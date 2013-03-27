#ifndef CS40_PRODUCTION_H
#define CS40_PRODUCTION_H

#include <QList>
#include <QString>

namespace cs40{
typedef struct prod_s {
  float weight;
  QString lhs;
  QList<QString> symbols;
} Production;
}

#endif
