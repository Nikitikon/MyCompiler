//
//  main.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include <iostream>
#include "Parser.hpp"
#include "DefaultSetting.hpp"
#include "list.hpp"

using namespace std;

int main()
{
    Parser* p = new Parser("Automat.txt");

    char* o = (char*)p->GetStartCondition();
    o = p->GetStartCondition();
    o = p->Find("newLine", "mmm");
    
    return 0;
}

