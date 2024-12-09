#!/bin/bash

# 0. Filtrar les files que tenen exactament 16 camps
awk -F',' '{ if (NF == 16) print $0 }' CAvideos.csv > supervivents.csv

# 1. Eliminar les columnes irrellevants: 'thumbnail_link' i 'description'
cut -d',' -f1-11,13-15 supervivents.csv > sortida.csv

# 2. Eliminar els registres on video_error_or_removed (camp 15) sigui "True"
awk -F',' '$14 != "True" { print $0 }' sortida.csv > sense_errors.csv

original_count=$(wc -l < sortida.csv) 
final_count=$(wc -l < sense_errors.csv)

eliminats=$((original_count - final_count))
echo "S'han eliminat $eliminats registres."

#3.Ranking_Views
echo "video_id,trending_date,title,channel_title,category_id,publish_time,tags,views,likes,dislikes,comment_count,comments_disabled,ratings_disabled,video_error_or_removed,Ranking_Views" > ranking.csv

awk -F',' 'BEGIN { OFS="," } 
FNR == 1 { next }  # Salta la primera línea
{
    if ($8 <= 1000000)
        ranking = "Bo";
    else if ($8 > 1000000 && $8 <= 10000000)
        ranking = "Excel·lent";
    else
        ranking = "Estrella";
    print $0, ranking
}' sense_errors.csv >> ranking.csv

#4.Rlikes, Rdislikes

input_file="ranking.csv"
output_file="p4.csv"
echo "video_id,trending_date,title,channel_title,category_id,publish_time,tags,views,likes,dislikes,comment_count,comments_disabled,ratings_disabled,video_error_or_removed,Ranking_Views,Rlikes,Rdislikes" > "$output_file"
count=0
while IFS=',' read -r video_id trending_date title channel_title category_id publish_time tags views likes dislikes comment_count; do
	((count++))
	if [[ $count -eq 1 ]]; then
        	continue
    	fi
    	if [[ "$views" -ne 0 ]]; then
        	Rlikes=$(echo "scale=2; $likes * 100 / $views" | bc)
        	Rdislikes=$(echo "scale=2; $dislikes * 100 / $views" | bc)
    	else
        	Rlikes=0  # No se puede calcular
        	Rdislikes=0  # No se puede calcular
	fi
    	echo "$video_id,$trending_date,$title,$channel_title,$category_id,$publish_time,$tags,$views,$likes,$dislikes,$comment_count,$Rlikes,$Rdislikes" >> "$output_file"
done < "$input_file"

#!/bin/bash

p4="p4.csv"

# Pedir al usuario que introduzca un identificador de vídeo o parte del título
echo "Introdueix l'identificador del vídeo o part del títol:"
read input_id
trobat=false
# Leer el archivo línea por línea
while IFS=',' read -r video_id trending_date title channel_title category_id publish_time tags views likes dislikes comment_count comments_disabled ratings_disabled video_error_or_removed Ranking_Views Rlikes Rdislikes
do
    # Comprobar si el video_id o parte del título coincide con la entrada del usuario
	if [[ "$video_id" == *"$input_id"* || "$title" == *"$input_id"* ]]; then
		echo "S'ha trobat una coincidència. A continuació es mostren els detalls:"
        	echo "Title: $title"
        	echo "Publish_time: $publish_time"
        	echo "Views: $views"
        	echo "Likes: $likes"
        	echo "Dislikes: $dislikes"
        	echo "Ranking_Views: $Ranking_Views"
        	echo "Rlikes: $Rlikes"
        	echo "Rdislikes: $Rdislikes"
        	echo ""
		trobat=true
	fi

done < "$p4"

if [[ "$trobat" == false ]]; then
	echo "No s'han trobat coincidències"
fi
