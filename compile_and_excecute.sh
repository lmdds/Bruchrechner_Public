std=c++17
printf "\e[1;31m >> Compiling : \e[0m \n"
g++ mainTest.cpp  Bruchberechner.cpp Berechner.cpp Bruch.cpp -o BruchrechnerTest -std=$std -Wall -I include
g++ main.cpp  Bruchberechner.cpp Berechner.cpp Bruch.cpp -o Bruchrechner -std=$std -Wall -I include
printf "\e[1;31m >> Done. Testing: \e[0m \n"
./BruchrechnerTest
printf "\e[1;31m >> Done. Executing Bruchrechner: \e[0m \n"
./Bruchrechner
