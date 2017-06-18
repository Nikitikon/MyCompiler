//
//  main.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include <iostream>
#include "UnaryOperationNode.hpp"
#include "VariableNode.hpp"

using namespace std;


int main()
{
//    Scope* s = new Scope();
//    Scope* sc = new Scope(s);
//    
//    sc->Put("Ponchik", 1, 1);
//    sc->Put("Krolic", 2, 1);
//    s->Put("Krolic", 3, 2);
//    s->Put("Chop", 4, 2);
//    
//    TValueKeeper* k = sc->Find("Ponchik");
//    k = sc->Find("Krolic");
//    k = sc->Find("Krolic");
//    k = sc->Find("Chop");
//    k = sc->Find("C");

    int a = 3, b = 2, c = 1;
    a = b = c;

    return 0;
}
