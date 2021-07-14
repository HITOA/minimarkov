#include <iostream>
#include <vector>
#include <string>
#include "minimarkov.hpp"

int main() {

    std::string a{"Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                  "Morbi ut scelerisque mi, eget dapibus libero. "
                  "Proin iaculis dolor vel lacus semper, quis "
                  "pretium lectus dapibus. Pellentesque elementum "
                  "neque at rhoncus euismod. Quisque gravida maximus velit, "
                  "id tincidunt arcu auctor non. Duis vitae turpis convallis "
                  "augue efficitur facilisis quis id mauris. Nunc auctor felis vitae "
                  "facilisis ultrices. Quisque non ligula vitae ante imperdiet bibendum. "
                  "Duis vitae augue eget justo dignissim convallis. Mauris a imperdiet libero. "
                  "Vestibulum eget ipsum maximus, sodales odio eget, venenatis "
                  "lacus. Aenean luctus hendrerit nulla, ac dignissim justo "
                  "dignissim nec. Quisque nec euismod ligula. Maecenas id bibendum magna, "
                  "a mollis nisi. Class aptent taciti sociosqu ad litora torquent "
                  "per conubia nostra, per inceptos himenaeos. Fusce "
                  "pulvinar purus ut tincidunt pharetra. Cras vulputate "
                  "efficitur turpis ac sollicitudin."}; //Data to train on

    MarkovChain<char> model; //markov chain model

    model.Train(a.begin(), a.end()); //training the model. take range iterator as argument.

    std::vector<char> b = model.Generate(500); //generate a output of size 50 max. it can be shorter if the generation end on a character with no link.

    std::copy(b.begin(), b.end(), std::ostreambuf_iterator(std::cout)); //print the result.

    /*
     * Result :
     * higu is vibe isod igena aus lim Ma eridis s idis m e aus mptodis im lisquen ae Penenis e ntont acibis ac n e is lat
     * Qura Macelisqur acibe ene s nacus ibe aenelis d n auibelela nenis ncumpet s ntor ve Mas lis lignet
     * pibiae Ma a e e s e ac isqur aue ve ige aper end is Mae m ntor is vis ibe s Duis l n acuctent ni arige
     * a ve ae ve e aer nt m encisqu acibis apisauis n. ve Aenenauligent acis as a
     * solet s aciacena e e is Qucigent pet a laum vis st Cr inari is s auibiberonte m s ige e aulis iguis la
     */

    return EXIT_SUCCESS;
}
