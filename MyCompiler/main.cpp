//
//  main.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include <iostream>
#include "FileReader.hpp"
#include "DefaultSetting.hpp"

using namespace std;

int main()
{
    FileReader* f = new FileReader("Automat.txt");
    
    cout << f->ReadLine();
    return 0;
}

