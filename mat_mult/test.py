import os

def main():

	nHilos=4;
	tamMat=100;
	operacion=1;
	nintentos=10;
	incremento=50;

	print("Compilando programa...")
	os.system("g++ -std=c++11 -pthread prueba1.cc -o main.out")

	filename=str(nHilos)+"_"+str(operacion)
	f= open(filename+".txt","w+") 

	print("Ejecutando...")
	for i in range(nintentos):
		parametros=str(nHilos)+" "+str(tamMat)+" "+str(operacion)+" "+filename
		result=int(os.system("./main.out "+parametros))/256
		print("result:{}".format(result))
		f.write(str(tamMat)+"-"+str(result)+"\n")
		#f.write(str(os.system("./main.out "+parametros))+"\n")
		tamMat+=incremento
	#f.close()
	pass

if __name__ == '__main__':
	main()