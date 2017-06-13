//
//  main.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include <iostream>
#include "Automat.hpp"
#include "DefaultSetting.hpp"
#include "list.hpp"

using namespace std;

int main()
{
    
    
    for (int i = 0; i < 1000; i++) {
        Automat* p = new Automat("Automat.txt");
        p->Work("int Ninor = rand(9999);");
    }

    return 0;
}

