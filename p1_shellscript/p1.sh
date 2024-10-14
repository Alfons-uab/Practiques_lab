#!/bin/bash

# 1. Filtrar les files que tenen exactament 16 camps
awk -F',' '{ if (NF == 16) print $0 }' CAvideos.csv > supervivents.csv

# 2. Eliminar les columnes irrellevants: 'thumbnail_link' i 'description'
cut -d',' -f1-12,13-15 supervivents.csv > sortida.csv

# 3. Eliminar els registres on video_error_or_removed (camp 15) sigui "True"
awk -F',' '$15 != "True" { print $0 }' sortida.csv > sense_errors.csv

# 4. Comptar els registres eliminats
original_count=$(wc -l < sortida.csv) 
final_count=$(wc -l < sense_errors.csv)

eliminats=$((original_count - final_count)) 
echo "S'han eliminat $eliminats registres."



# 5. Afegir l'encapçalament al fitxer amb la columna Ranking_Views
echo "video_id,trending_date,title,channel_title,category_id,publish_time,tags,views,likes,dislikes,comment_count,comments_disabled,ratings_disabled,video_error_or_removed,Ranking_Views" > ranking.csv

# 6. Afegir la columna Ranking_Views en funció de les visualitzacions
awk -F',' 'BEGIN { OFS="," } {
    if ($8 <= 1000000)
        ranking = "Bo";
    else if ($8 > 1000000 && $8 <= 10000000)
        ranking = "Excel·lent";
    else
        ranking = "Estrella";
    print $0, ranking
}' sense_errors.csv >> ranking.csv

# Afegir la columna Rlikes i Rdislikes com a percentatges
echo "video_id,trending_date,title,channel_title,category_id,publish_time,tags,views,likes,dislikes,comment_count,comments_disabled,ratings_disabled,video_error_or_removed,ranking,rlikes,rdislikes" > processat.csv

# Llegir cada línia (a partir de la segona) i calcular Rlikes i Rdislikes
tail -n +2 ranking.csv | while IFS=',' read -r video_id trending_date title channel_title category_id publish_time tags views likes dislikes comment_count comments_disabled ratings_disabled video_error_or_removed ranking
do
    # Comprovar que views sigui més gran que 0 per evitar divisions per zero
    if [ "$views" -gt 0 ]; then
        # Càlcul de Rlikes i Rdislikes com a percentatge
        rlikes=$(echo "scale=2; ($likes * 100) / $views" | bc)
        rdislikes=$(echo "scale=2; ($dislikes * 100) / $views" | bc)
    else
        rlikes=0
        rdislikes=0
    fi

    # Afegir les noves columnes al fitxer processat
    echo "$video_id,$trending_date,$title,$channel_title,$category_id,$publish_time,$tags,$views,$likes,$dislikes,$comment_count,$comments_disabled,$ratings_disabled,$video_error_or_removed,$ranking,$rlikes,$rdislikes" >> processat.csv
done
