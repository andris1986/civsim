#include "CTribe.h"

CTribe::CTribe() {

}

void CTribe::addCreature(CCreature & c) {
	m_creatures.push_back(&c);
}

void CTribe::removeCreature(CCreature & c) {
	m_creatures.remove(&c);
}
