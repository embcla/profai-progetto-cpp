#include "../include/items.h"
#include <string>
#include <list>
#include <algorithm>

// Item class implementation
Item::Item() : _id(0) {
}

// Note: Template class implementations must be in the header file
// because they need to be available at compile time when instantiated.
// If you need to use ItemList with specific types only, you can
// explicitly instantiate them here instead.

// Example explicit template instantiations (uncomment if needed):
// template class ItemList<cliente>;
// template class ItemList<contract>;
// template class ItemList<appointment>;
