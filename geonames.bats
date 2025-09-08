tests_folder=tests
prog=geonames
help_first_line="Usage: ./geonames <NUMBER OF CITIES>"


@test "test0 : Aucun argument" {
    
    touch test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "nombre arguments invalide" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "test1 : Trop d arguments" {
   
    echo "4 5 2" > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 1 ]
    [ "${lines[0]}" = "nombre arguments invalide" ]
    [ "${lines[1]}" = "$help_first_line" ]
}

@test "test2 : Nombre de ville trop petit" {
    
    echo 0 > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 2 ]
    [ "${lines[0]}" = "nombre de ville invalide" ]
}

@test "test3 : Nombre de ville trop grand" {
    
    echo 5001 > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 2 ]
    [ "${lines[0]}" = "nombre de ville invalide" ]
}

@test "test4 : Argument caractère" {
    
    echo K > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 3 ]
    [ "${lines[0]}" = "type argument invalide" ]
}

@test "test5 : Argument chaine de caracteres" {
    
    echo INF3135 > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 3 ]
    [ "${lines[0]}" = "type argument invalide" ]
}

@test "test6 : afficher tableau de 5 villes" {
    
    echo 5 > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang	Nom                        	Pays                                          	Population" ]
    [ "${lines[1]}" = "----	---                        	----                                          	----------" ]
    [ "${lines[2]}" = "1	Shanghai                      	China                                   	22315474" ]
    [ "${lines[6]}" = "5	Kinshasa                      	Democratic Republic of the Congo        	16000000" ]
}

@test "test7 : affiche 1 ville" {
    
    echo 1 > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang	Nom                        	Pays                                          	Population" ]
    [ "${lines[1]}" = "----	---                        	----                                          	----------" ]
    [ "${lines[2]}" = "1	Shanghai                      	China                                   	22315474" ]
}

@test "test8 : affiche 10 villes" {
    
    echo 10 > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang	Nom                        	Pays                                          	Population" ]
    [ "${lines[1]}" = "----	---                        	----                                          	----------" ]
    [ "${lines[2]}" = "1	Shanghai                      	China                                   	22315474" ]
    [ "${lines[10]}" = "9	Mumbai                        	India                                   	12691836" ]
}

@test "test9 : affiche 5000 villes" {
   
    echo 5000 > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang	Nom                        	Pays                                          	Population" ]
    [ "${lines[1]}" = "----	---                        	----                                          	----------" ]
    [ "${lines[2]}" = "1	Shanghai                      	China                                   	22315474" ]
    [ "${lines[5001]}" = "5000	Gusong                        	China                                   	87882" ]
    
}

@test "test10 : affiche 2500 villes" {
   
    echo 2500 > test.txt;run ./$prog < test.txt;rm test.txt
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Rang	Nom                        	Pays                                          	Population" ]
    [ "${lines[1]}" = "----	---                        	----                                          	----------" ]
    [ "${lines[2]}" = "1	Shanghai                      	China                                   	22315474" ]
    [ "${lines[2500]}" = "2499	Legaspi                       	Philippines                             	179481" ]
}
