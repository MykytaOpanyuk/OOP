
#include "stdafx.h"
#include <iostream>
#include <string>
#include "market.h"
#include "Group.h"
#include "product.h"

using namespace std;

int main() {
	market products;	

	RB_tree tree(products);
	system("pause");
	return 0;

}

