#ifndef REALIZZAZIONI_ARRAYSORT_H
#define REALIZZAZIONI_ARRAYSORT_H
void mergeSort(int v[], int p, int u);
void merge(int v[],int p,int m,int u);




void mergeSort(int v[], int p, int u)
{
    if (p<u)
    {
        int m=p+(u-p)/2;
        mergeSort(v,p,m);
        mergeSort(v,m+1,u);
        merge(v,p,m,u);
    }
}
void merge(int v[],int p,int m,int u)
{
    int dim1,dim2;
    dim1=m-p+1;
    dim2=u-m;
    int v1[dim1];
    int v2[dim2];

    for (int i=0;i<dim1;i++)
    {
        v1[i]=v[i+p];
    }
    for (int j=0;j<dim2;j++)
    {
        v2[j]=v[m+j+1];
    }

    int i=0,j=0,k=p;
    while (i<dim1 && j<dim2)
    {
        if (v1[i]<v2[j])
        {
            v[k]=v1[i];
            i++;
        }
        else
        {
            v[k]=v2[j];
            j++;
        }
        k++;
    }
    while (i<dim1)
    {
        v[k]=v1[i];
        i++;
        k++;
    }
    while (j<dim2)
    {
        v[k]=v2[j];
        j++;
        k++;
    }

}
#endif //REALIZZAZIONI_ARRAYSORT_H
