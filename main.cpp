#include "config.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"
#include "translator.hpp"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    std::string file = argv[1];

    Config::conf().set(LOG_OUTPUT, 1);

    Translator translator({});
    translator.init();
    int line_index = 0;
    forline(file.c_str(), [&translator, &line_index](char **line) {
        std::cout << ";;-------\n";

        std::cout << "\n\n;; [LINE] " << (*line) <<";; len|" << strlen(*line) << "\n";
        if (strlen(*line) <= 2 || !((*line)[0] == '/' && ((*line)[1] == '/'))) {
            Tokenizer tokenizer(*line);
            auto toks = tokenizer.tokenize();

            Parser parser(toks);
            auto postfix = parser.postfix();
            std::cout << ";;------- POSTFIX\n";

            for (int i = 0; i < postfix.size(); ++i) {
                postfix[i].logtok();
            }
            std::cout << ";;------- //POSTFIX\n";

            translator.update(postfix);
            translator.update(line_index);
            translator.translate();
            line_index ++;

        } else {
            std::cout<<";;\t [COMMENT]\n";
        }
        
    });

    std::cout << ";;<<END\n";
}