# SimCity

in order to compile with no errors you need to use this line

g++ -std=c++11 main.cpp Config.cpp Region.cpp -o simulation

./simulation


Okay i Basically set up the whole program bases, all you need to do now is add the new zones to the Cell Class and then have
them update automatically based of the timeLimit and refresh rate thats given. 

so in Cell class you would essentially add under zoneType and public:
int population
int pollution 
and so on

- Ronnie
