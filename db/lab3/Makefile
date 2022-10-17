.PHONY: part1 part2 part3 part4
FLAGS=-U ex4to -d labs_db -q

all: part1 part2 part3 part4

part1:
	psql -c '\i $@.sql' -U postgres -d labs_db -q

part2:
	psql -c '\i $@.sql' $(FLAGS)

part3:
	psql -c '\i $@.sql' $(FLAGS)
