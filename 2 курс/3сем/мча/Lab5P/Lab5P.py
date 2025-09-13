import numpy as np
from jacobi_eigen_method import find_eigen
from staff import print_array, is_matrix_symmetric
import task
import test

E = task.E
A = task.A
A1 = test.A_1
A2=test.A_2
A3=test.A_3

print("\nTask")
if not is_matrix_symmetric(A, 0.000001):
    print("Matrix not symmetric")
    exit(0)

eig_val, eig_vec, steps = find_eigen(A, E, 1)

print_array(A, 'Default Matrix:')
print_array(eig_val, '\nMatrix of Eigenvalues:')
print_array(eig_val @ np.ones(shape=(eig_val.shape[0], )), 'Eigenvalues:')
print_array(eig_vec, 'Eigenvectors:')


print("\nVerification:")

w, v = np.linalg.eig(A)
print_array(w, 'Eigenvalues (numpy):')
print_array(v, 'Eigenvectors (numpy):')

###
print("\nExample 1")

if not is_matrix_symmetric(A1, 0.000001):
    print("Matrix not symmetric")
    exit(0)

eig_val, eig_vec, steps = find_eigen(A1, E, 1)

print_array(A1, 'Default Matrix:')
print_array(eig_val, '\nMatrix of Eigenvalues:')
print_array(eig_val @ np.ones(shape=(eig_val.shape[0], )), 'Eigenvalues:')
print_array(eig_vec, 'Eigenvectors:')


print("\nVerification:")

w, v = np.linalg.eig(A1)
print_array(w, 'Eigenvalues (numpy):')
print_array(v, 'Eigenvectors (numpy):')

###
print("\nExample 2")
if not is_matrix_symmetric(A2, 0.000001):
    print("Matrix not symmetric")
    exit(0)

eig_val, eig_vec, steps = find_eigen(A2, E, 1)

print_array(A2, 'Default Matrix:')
print_array(eig_val, '\nMatrix of Eigenvalues:')
print_array(eig_val @ np.ones(shape=(eig_val.shape[0], )), 'Eigenvalues:')
print_array(eig_vec, 'Eigenvectors:')


print("\nVerification:")

w, v = np.linalg.eig(A2)
print_array(w, 'Eigenvalues (numpy):')
print_array(v, 'Eigenvectors (numpy):')

###
print("\nExample 3")
if not is_matrix_symmetric(A3, 0.000001):
    print("Matrix not symmetric")
    exit(0)

eig_val, eig_vec, steps = find_eigen(A3, E, 1)

print_array(A3, 'Default Matrix:')
print_array(eig_val, '\nMatrix of Eigenvalues:')
print_array(eig_val @ np.ones(shape=(eig_val.shape[0], )), 'Eigenvalues:')
print_array(eig_vec, 'Eigenvectors:')


print("\nVerification:")

w, v = np.linalg.eig(A3)
print_array(w, 'Eigenvalues (numpy):')
print_array(v, 'Eigenvectors (numpy):')

