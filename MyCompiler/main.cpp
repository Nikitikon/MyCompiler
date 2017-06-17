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

    TValue* v = new TValue(1,0);
    cout << v->GetValue() << endl;
    VariableNode* vn = new VariableNode(v);
    UnaryOperationNode *u = new UnaryOperationNode(3, vn);
    u->Execute();
    cout << v->GetValue() << endl;

    return 0;
}
