
#!/bin/bash

# 0. Filtrar les files que tenen exactament 16 camps
awk -F',' '{ if (NF == 16) print $0 }' CAvideos.csv > supervivents.csv

# 1. Eliminar les columnes irrellevants: 'thumbnail_link' i 'description'
cut -d',' -f1-11,13-15 supervivents.csv > sortida.csv

# 2. Eliminar els registres on video_error_or_removed (camp 15) sigui "True"
awk -F',' '$14 != "True" { print $0 }' sortida.csv > sense_errors.csv

#filtra les linies on la columna 14 es false i les passa a un altre arxiu on les files amb errors no estaran
original_count=$(wc -l < sortida.csv) 
final_count=$(wc -l < sense_errors.csv)

#conta les linies dels dos arxius
eliminats=$((original_count - final_count))
echo "S'han eliminat $eliminats registres."

#3. Crear una nova columna Ranking_Views on depenent de les visualitzacions seran:bons(amb 1000000 o menys visualitzacions),excel·lents(entre 1000000 i 10000000 visualitzacions) o estrelles(amb més de 10000000 visualitzacions)
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
#compara el nombre de visites i classifica segons la quantitat de visites
    print $0, ranking
}' sense_errors.csv >> ranking.csv

#4.crear dues noves columnes Rlikes i Rdislikes on es calculara el percentatge de likes vigilan que les visualitzacions no siguin zero amb el calcul:likes(o dislikes)*100/views(les visites)
input_file="ranking.csv"
output_file="p4.csv"
echo "video_id,trending_date,title,channel_title,category_id,publish_time,tags,views,likes,dislikes,comment_count,comments_disabled,ratings_disabled,video_error_or_removed,Ranking_Views,Rlikes,Rdislikes" > "$output_file"
count=0
while IFS=',' read -r video_id trending_date title channel_title category_id publish_time tags views likes dislikes comment_count; do
	((count++))
	if [[ $count -eq 1 ]]; then
        	continue
    	fi
    	if [[ "$views" -ne 0 ]]; then #assegurem que el nombre de visites no sigui zero
        	Rlikes=$(echo "scale=2; $likes * 100 / $views" | bc)
        	Rdislikes=$(echo "scale=2; $dislikes * 100 / $views" | bc)
    	else #si views es 0 no es podra fer la divisió pertant es queda a 0
        	Rlikes=0  # No se puede calcular
        	Rdislikes=0  # No se puede calcular
	fi
    	echo "$video_id,$trending_date,$title,$channel_title,$category_id,$publish_time,$tags,$views,$likes,$dislikes,$comment_count,$Rlikes,$Rdislikes" >> "$output_file"
done < "$input_file"

p4="p4.csv"

#5. demanar a l'usuari que introdueixi un identificador per al video(likes, titol,...)no cal que el titol estigui sencer
echo "Introdueix l'identificador del vídeo o part del títol:"
read input_id
trobat=false

p4="p4.csv"
if [[ ! -f "$p4" ]]; then
    echo "L'arxiu $p4 no existeix."
    exit 1 #comprova que l'arxiu on es busca el video existeixi i sino existeix surt del programa
fi

#Llegim l'arxiu linea a linea
while IFS=',' read -r video_id trending_date title channel_title category_id publish_time tags views likes dislikes comment_count comments_disabled ratings_disabled video_error_or_removed Ranking_Views Rlikes Rdislikes
do
    # Mirem si el video_id o part del títul coincideix amb l'entrada de l'usuari
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
