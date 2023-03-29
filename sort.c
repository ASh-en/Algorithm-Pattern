/*************************************************************************
*File Name: sort.c
*Author: Ash
*mail: shen150104@163.com
*Created Time: 2023年03月17日 星期五 12时08分47秒
 ************************************************************************/

/*************************************************************************
*Func Name: scanf_data
*Created Time: 2023年03月17日 星期五 12时08分47秒
 ************************************************************************/
int scanf_data(int q[])
{
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i ++) scanf("%d", &q[i]);
    return n;
}



/*************************************************************************
*Func Name: quick_sort
*Created Time: 2023年03月17日 星期五 12时08分47秒
 ************************************************************************/
void quick_sort(int q[], int l, int r)
{
    if(l >= r) return;
    int i = l-1,j = r+1,x = q[l+r>>1];//x = q[l+r+1>>2]
    while(i < j)
    {
         do i++;while(q[i]<x);
         do j--;while(q[j]>x);
         if(i<j) swap(q[i],q[j]);
    }
    quick_sort(q,l,j),quick_sort(q,j+1,r);//quick_sort(q,l,i-1),quick_sort(q,i,r);
}


/*************************************************************************
*Func Name: merge_sort
*Created Time: 2023年03月17日 星期五 12时08分47秒
 ************************************************************************/
int tmp[];
void merge_sort(int q[], int l, int r)
{
    if(l >= r) return;

    int mid = l + r >> 1;
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if(q[i] <= q[j]) tmp[k ++] = q[i ++];
        else tmp[k ++] = q[j ++];
    while (i <= mid) tmp[k ++] = q[i ++];
    while (j <= r) tmp[k ++] = q[j ++];
    
    for (i = l, j = 0; i <= r; i ++,j ++) q[i] = tmp[j];
}



























