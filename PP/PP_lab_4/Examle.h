#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int size, rank, i;
    MPI_Init(&argc, &argv);                 /* �������������� ���������� */
    MPI_Comm_size(MPI_COMM_WORLD, &size);   /* ������ ���������� ����� � ���������� ���������� */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* ... � ���� ����������� �����: �� 0 �� (size-1) */

    /* ������ � ������� 0 �������� ������������ ������ ������,
       � ������� ����������� ������� �����,
       � ���������� (��������������) MPI_COMM_WORLD,
       �.�. ����� ��������� � ����������!!*/
    if (rank == 0)
        printf("Total processes count = %d\n", size);
    fflush(stdout);  /* ������� ����� ������ */

    printf("Hello! My rank in MPI_COMM_WORLD = %d\n", rank);  /* ������ ������ ������� ������������ ���� ����� */
    fflush(stdout);  /* ������� ����� ������ */

    MPI_Barrier(MPI_COMM_WORLD);  /* ����� ������������� */

    /* ������ 0 �������� ��������� ��������� ������.
       � ��������� ������ ����� ���� ���������,
       ����������� ����������� MPIRUN.*/
    if (rank == 0) {
        printf("Command line of process 0: ");
        for (i = 0; i < argc; i++)
            printf("%d: \"%s\"\n", i, argv[i]);
        fflush(stdout);  /* ������� ����� ������ */
    }

    MPI_Finalize();  /* ��� ������ ��������� ���������� */
    return 0;
}