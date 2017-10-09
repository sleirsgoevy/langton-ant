ant_chunks: ant.cpp storage_chunks.cpp
	g++ $(CPPFLAGS) -o ant_chunks ant.cpp storage_chunks.cpp

ant_lru: ant.cpp storage_lru.cpp
	g++ $(CPPFLAGS) -o ant_lru ant.cpp storage_lru.cpp
