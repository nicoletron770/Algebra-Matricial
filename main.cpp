//Ajuste de polinomios
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
    int i,j,k,n,N;
    cout.precision(4);//ajustamos la precision a 4
    cout.setf(ios::fixed);//esto hace que en efecto que ponga la precision en 4
    cout<<"\nIngrese el numero de pares ordenados:\n";//Pedimos el numero de datos para asignar las dimensiones de las matrices
    cin>>N;
    double x[N],y[N]; //Aqui definimos los vectores de tamaño N
    cout<<"\nIngrese el valor de x del par ordenado:\n";//Para ingresar los valores x de cada par ordenado
    for (i=0;i<N;i++)
        cin>>x[i];//Aqui vamos agregando los valores de x al vector ordenados
    cout<<"\nIngrese el valor de y del par ordenado:\n";//Para ingresar los valores y de cada par ordenado
    for (i=0;i<N;i++)
        cin>>y[i];//Aqui vamos agregando los valores de y al vector ordenados
    cout<<"\nIngrese el grado de polinomio que vaya a usar:\n";
    cin>>n;//n es el grado del polinomio
    double X[2*n+1];//Se define el arreglo en donde se guardan los valores de sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    for (i=0;i<2*n+1;i++)
    {
        X[i]=0;
        for (j=0;j<N;j++)
            X[i]=X[i]+pow(x[j],i);//Aqui se guardan los valores de la matriz que se definio arriba, estos son, N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    }
    double B[n+1][n+2],a[n+1];//B es la matriz normal aumentada que guarda los valores de las ecuaciones, 'a' guarda los valores finales de los coeficientes
    for (i=0;i<=n;i++)
        for (j=0;j<=n;j++)
            B[i][j]=X[i+j];//Construye la matriz normal guardando los coeficientes correspondientes en la posicion exacta a excepcion de la ultima columna de la matriz
    double Y[n+1];//Arreglo para guardar los valores de sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    for (i=0;i<n+1;i++)
    {
        Y[i]=0;
        for (j=0;j<N;j++)
        Y[i]=Y[i]+pow(x[j],i)*y[j];//Aqui se guardan los valores de la matriz sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    }
    for (i=0;i<=n;i++)
        B[i][n+1]=Y[i];//Junta los valores de Y a la ultima columna de la matriz normal aumentada B
    n=n+1;//n se cambia a n+1 porque en la parte de eliminacion gaussiana es para n ecuaciones, pero anteriormente n es el grado del polinomio y para n grados tenemos n+1 ecuaciones
   /* cout<<"\nMatriz normal aumentada:\n";
    for (i=0;i<n;i++)//Matriz normal aumentada
    {
        for (j=0;j<=n;j++)
            cout<<B[i][j]<<setw(16); sisirrrrveeeee
        cout<<"\n";
    }*/
    for (i=0;i<n;i++)//Aqui empieza la eliminacion gaussiana para las n+1 ecuaciones
        for (k=i+1;k<n;k++)
            if (B[i][i]<B[k][i])
                for (j=0;j<=n;j++)
                {
                    double temp=B[i][j];
                    B[i][j]=B[k][j];
                    B[k][j]=temp;
                }

    for (i=0;i<n-1;i++)//ciclo para hacer la eliminacion
        for (k=i+1;k<n;k++)
            {
                double t=B[k][i]/B[i][i];
                for (j=0;j<=n;j++)
                    B[k][j]=B[k][j]-t*B[i][j];//aqui se hace la matriz triangular superior con el pivote
            }
    for (i=n-1;i>=0;i--)//sustitucion inversa
    {                        //x es un arreglo con valores correspondientes a x,y,z..
        a[i]=B[i][n];                // hace que la variable calculada sea igual al lado derecho de la ultima ecuacion
        for (j=0;j<n;j++)
            if (j!=i)//despues resta todos los valores del lado izquierdo a excepcion del coeficiente de la variable que esta siendo calculada
                a[i]=a[i]-B[i][j]*a[j];
        a[i]=a[i]/B[i][i];//divide el lado derecho por el coeficiente de la variable calculada
    }
    cout<<"\nLos valores de los coeficientes son:\n";
    for (i=0;i<n;i++)
        cout<<"x^"<<i<<"="<<a[i]<<endl;
    cout<<"\nPor lo tanto, la ecuacion de ajuste es:\ny=";
    for (i=0;i<n;i++)
        cout<<" + ("<<a[i]<<")"<<"x^"<<i;
    cout<<"\n";
    return 0;
}
