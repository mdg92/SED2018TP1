[top]
components : neighbour@neighbour growing_field farmer@farmer
out : sat usd amb next_field
in: swcg ext
link : u_amb@farmer amb
link : u_usd@farmer usd
link : field@farmer next_field
link : satisfaction@farmer sat

link : swcg wgc@farmer
link : res_amb@growing_field r_amb@farmer
link : res_usd@growing_field r_usd@farmer
link : costed@growing_field cost@farmer
link : out@neighbour neighbour@farmer


link : out@neighbour best_neigh@growing_field 
link : field@farmer upcomming_field@growing_field 
link : ext events@growing_field 
link : swcg swcg@growing_field 


[growing_field]
components : field@field  table@table
out: res_usd res_amb costed
in: best_neigh upcomming_field events swcg
link : cost@table costed
link : r_amb@table res_amb
link : r_usd@table res_usd
link : swcg wgc@table
link : best_neigh best_neighbour@table
link : events external_change@table
link : reaped@field field@table
link : upcomming_field seed@field