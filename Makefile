bats = bats/bats-core/bin/bats
CC = gcc
OPTIONS = -std=c99 -DNDEBUG -Wall

# Build
# -----

build: geonames


geonames: geonames.c fichier-cities15000 fichier-countryInfo
	$(CC) $(OPTIONS) -o $@ $<

motzkin: motzkin.c
	$(CC) $(OPTIONS) -o $@ $<

# Telechargement des fichier de geonames
# ----	

fichier-countryInfo:
	wget https://download.geonames.org/export/dump/countryInfo.txt

fichier-cities15000:
	wget https://download.geonames.org/export/dump/cities15000.zip
	unzip cities15000.zip

# Test
# ----

test: test-geonames

test-geonames: geonames geonames.bats
	$(bats) geonames.bats

# Clean
# ----

Clean:
	rm cities15000.txt
	rm -r cities15000.zip
	rm countryInfo.txt
	rm geonames
	

