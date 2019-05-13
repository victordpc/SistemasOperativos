

Fichero="";
MaxCpu=1;


# recogemos y validamos el fichero
echo "Introduzca un fichero con los datos para la simulación"
read Fichero


while [ ! -f $Fichero]
do
	echo "No existe el fichero o no es un fichero regular"
	echo "Introduzca un fichero con los datos para la simulación"
	read Fichero
done
# recogemos y validamos el fichero
Fichero="./"$Fichero

# recogemos y validamos el numero de CPU
echo "Introduzca un número de CPUs para probrar en la simulación"
read MaxCpu


while [ 0 > $MaxCpu  || $MaxCpu > 8 ]
do
	echo $MaxCpu" no es un valor válido"
	echo "Introduzca un número de CPUs para probrar en la simulación, el valor debe ser en el rango [0-8]"
	read MaxCpu
done
# recogemos y validamos el numero de CPU


# creamos directorio
mkdir ./resultados
# creamos directorio


# creamos los logs de CPUS
for i in $MaxCpu
do
	#Creamos logs
	./schedsim/schedsim -n $i -i $Fichero -s RR
	#Movemos ficheros
	for j in $i
	do
		mv "CPU_"$j".log" "./resultados/RR_CPU_"$j"de"$i".log"
	done

	#Creamos logs
	./schedsim/schedsim -n $i -i $Fichero -s SJF -p
	#Movemos ficheros
	for j in $i
	do
		mv "CPU_"$j".log" "./resultados/SJF_CPU_"$j"de"$i".log"
	done

	#Creamos logs
	./schedsim/schedsim -n $i -i $Fichero -s FCFS
	#Movemos ficheros
	for j in $i
	do
		mv "CPU_"$j".log" "./resultados/FCFS_CPU_"$j"de"$i".log"
	done

	#Creamos logs
	./schedsim/schedsim -n $i -i $Fichero -s PRIO -p
	#Movemos ficheros
	for j in $i
	do
		mv "CPU_"$j".log" "./resultados/PRIO_CPU_"$j"de"$i".log"
	done

done

# creamos las imagenes
for archivo in ls ./resultados
do
	./gantt-gplot/generate_gantt_chart ./resultados/$archivo
done
# creamos las imagenes
