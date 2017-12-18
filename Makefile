ant_chunks: ant.cpp storage_chunks.cpp
	g++ $(CPPFLAGS) -o ant_chunks ant.cpp storage_chunks.cpp

ant_lru: ant.cpp storage_lru.cpp
	g++ $(CPPFLAGS) -o ant_lru ant.cpp storage_lru.cpp

ant_trie/ant.a:
	cd ant_trie; make ant.a

ant-trie.a: ant_trie/ant.a
	cp ant_trie/ant.a ant-trie.a
