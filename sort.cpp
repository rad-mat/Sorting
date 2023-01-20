#include "sort.h"

void Update( int*, int, int );
void QuickSort2( int*, int, int );

void InsertionSort( int* t, int n )
{
    for( int i = 1; i < n; i++ )
    {
        int temp = t[i];
        int j = i - 1;
        while( j >= 0 && t[j] >= temp )
        {
            t[j + 1] = t[j--];
        }
        t[j + 1] = temp;
    }
}

void SelectionSort( int* t, int n )
{
    for( int i = 0; i < n - 1; i++ )
    {
        int temp = t[i];
        int k = i;
        for( int j = i + 1; j < n; j++ )
        {
            if( t[j] < temp )
            {
                temp = t[j];
                k = j;
            }
        }
        t[k] = t[i];
        t[i] = temp;
    }
}

void BubbleSort( int* t, int n )
{
    for( int j = n - 1; j > 0; j-- )
    {
        for( int i = 0; i < n - 1; i++ )
        {
            if( t[i] > t[i + 1] )
            {
                int temp = t[i];
                t[i] = t[i + 1];
                t[i + 1] = temp;
            }
        }
    }
}

void MixedSort( int* t, int n )
{
    int l = 1; 
    int p = n-1; 
    int k = n-1;
    do
    {
        for( int j = p; j >= l; j-- )
        {
            if( t[j - 1] > t[j] )
            {
                int temp = t[j - 1];
                t[j - 1] = t[j];
                t[j] = temp;
                k = j;
            }
        }
        l = k + 1;
        for( int j = l; j <= p; j++ )
        {
            if( t[j - 1] > t[j] )
            {
                int temp = t[j - 1];
                t[j - 1] = t[j];
                t[j] = temp;
                k = j;
            }
        }
        p = k - 1;
    } while( l <= p );
}

void HalfInsertSort( int* t, int n )
{
    for( int i = 1; i < n; i++ )
    {
        int temp = t[i];
        int l = 0;
        int p = i - 1;
        while( l <= p )
        {
            int m = ( l + p ) / 2;
            if( temp < t[m] ) p = m - 1;
            else l = m + 1;
        }
        for( int j = i - 1; j >= l; j-- )
        {
            t[j + 1] = t[j];
        }
        t[l] = temp;
    }
}

void Update( int* t, int l, int p )
{
    if( l == p ) return;
    int i = l;
    int j = 2 * i + 1;
    int temp = t[i];
    while( j <= p )
    {
        if( j < p )
        {
            if( t[j] < t[j + 1] ) j++;
        }
        if( temp >= t[j] ) break;
        t[i] = t[j];
        i = j;
        j = 2 * i + 1;
    }
    t[i] = temp;
}

void HeapSort( int* t, int n )  
{
    for( int l = n / 2 - 1; l >= 0; l-- )
    {
        Update( t, l, n - 1 );
    }

    for( int p = n - 1; p > 0; p-- )
    {
        int temp = t[0];
        t[0] = t[p];
        t[p] = temp;
        Update( t, 0, p - 1 );
    }
}

void Update_rosnaco( int* t, int l, int p )
{
    if( l == p ) return;
    int rodzic = l;
    int lewe_dziecko = 2 * rodzic + 1;
    int temp = t[rodzic];
    while( lewe_dziecko <= p )
    {
        if( lewe_dziecko < p )      
        {
            if( t[lewe_dziecko] < t[lewe_dziecko + 1] ) lewe_dziecko++;     
        }
        if( temp >= t[lewe_dziecko] ) break;
        t[rodzic] = t[lewe_dziecko];  
        rodzic = lewe_dziecko;
        lewe_dziecko = 2 * rodzic + 1;
    }
    t[rodzic] = temp;
}

void HeapSort_rosnaco( int* t, int n )             
{
    for( int l = n / 2 - 1; l >= 0; l-- )   
    {
        Update_rosnaco( t, l, n - 1 );  
    }

    for( int p = n - 1; p > 0; p-- ) 
    {
        int temp = t[0];          
        t[0] = t[p];
        t[p] = temp;
        Update_rosnaco( t, 0, p - 1 );       
    }
}

void Update_malejaco( int* t, int l, int p )
{
    if( l == p ) return;
    int rodzic = l;
    int lewe_dziecko = 2 * rodzic + 1;
    int temp = t[rodzic];
    while( lewe_dziecko <= p )
    {
        if( lewe_dziecko < p ) 
        {
            if( t[lewe_dziecko] > t[lewe_dziecko + 1] ) lewe_dziecko++;   
        }
        if( temp <= t[lewe_dziecko] ) break;
        t[rodzic] = t[lewe_dziecko];  
        rodzic = lewe_dziecko;
        lewe_dziecko = 2 * rodzic + 1;
    }
    t[rodzic] = temp;
}

void HeapSort_malejaco( int* t, int n )           
{
    for( int l = n / 2 - 1; l >= 0; l-- )  
    {
        Update_malejaco( t, l, n - 1 );      
    }

    for( int p = n - 1; p > 0; p-- )    
    {
        int temp = t[0];                
        t[0] = t[p];
        t[p] = temp;
        Update_malejaco( t, 0, p - 1 );    
    }
}


void QuickSort( int* t, int n )        
{
    QuickSort2( t, 0, n-1 );
}

void QuickSort2( int* t, int l, int p )
{
    int i = l;
    int j = p;
    int pivot = t[( l + p ) / 2];
    do
    {
        while( t[i] < pivot ) i++;
        while( t[j] > pivot ) j--;
        if( i <= j )
        {
            int temp = t[i];
            t[i++] = t[j];
            t[j--] = temp;
        }
    } while( i <= j );
    
    if( j > l ) QuickSort2( t, l, j );
    if( i < p ) QuickSort2( t, i, p );
}