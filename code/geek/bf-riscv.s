#
# This program is part of Occam's Razor Number 7
# Copyright (C) 2024 Occam's Razor
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
	.text
	.global _start
	.equ MEM_SIZE, 2048
_start:
	# Lee datos desde entrada estándar
	la   a1, mem
	move t1, zero
	li   t2, 0x20
bucle01:	
	li   a7, 63
	li   a0, 0
	li   a2, 1
	ecall
	# Si <=0 (EOF) terminamos bucle
	blez a0, cont01
	
	lb  t0, 0(a1)
	ble t0,t2, bucle01  # Elimina espacios
	
	add t1, t1, 1
	add a1, a1, 1
	j   bucle01
cont01:
	la  t2, mem     # Contador de programa (2K inferiores código)
	li  t4, MEM_SIZE / 2
	add t6, t2, t4  # Puntero de datos (2K superiores datos)
	                # addi solo puede sumar numeros de 12 bits con signo.
	                # Valor maximo 2047
	add t3, t2, t1  # Apunta al final del programa
	
bucle02: # Main Loop	
	lb  t4, 0(t2)
	li  t5, '<'
	beq t4, t5, inc_data_ptr
	li  t5, '>'
	beq t4, t5, dec_data_ptr
	li  t5, '+'
	beq t4, t5, inc_data
	li  t5, '-'
	beq t4, t5, dec_data
	li  t5, '.'
	beq t4, t5, print_data
	li  t5, ','
	beq t4, t5, read_data
	li  t5, '['
	beq t4, t5, while_start
	li  t5, ']'
	beq t4, t5, while_end
	# Simplemente ignora cualquier otro caracter
	j cont02
	
while_start:
	sd   t2, 0(sp)    # Push contador de programa
	add  sp, sp, -8 
	
	lb   t4, 0(t6)    
	bnez t4, cont02   # Si data no es cero.. continua,
	                  # Si data es cero... Salta al final del bucle
	li   a1, 1        # En a1 contamos corchetes. Empezamos con 1
bucle03:		
	add  t2, t2, 1    # Nos saltamos el corchete actual
	lb   t4, 0(t2)    # Leemos instruccion actual
	                  # Si encontramos [ Sumamos 1 a a1.
	                  # Si encontramos ] restamos 1
	                  # Cuando a1 valga cero habremos encontrado el corchete correcto
	li   t5, '['     
	beq  t4, t5, incrementa
	li   t5, ']'
	beq  t4, t5, decrementa
	j    bucle03
incrementa:
	add a1, a1, 1     # Cuando sumamos nunca nos dará cero
	j   bucle03
decrementa:
	add  a1, a1, -1
	bnez a1, bucle03 
	j    cont02

while_end:
	lb   t4, 0(t6)
	beq  t4, zero, cont04  # Si data es cero.. continua,
	ld   t2, 8(sp)         # Sino, salta al principio del bucle
	j    cont02
cont04:
	add  sp, sp, +8  # Hemos terrminado el bucle. Eliminamos de la pila
	j    cont02
	
inc_data_ptr:
	add  t6, t6, 1
	j    cont02
dec_data_ptr:
	add  t6, t6, -1
	j    cont02
inc_data:
	lb   t1, 0(t6)
	add  t1, t1, 1
	sb   t1, 0(t6)
	j    cont02
dec_data:
	lb   t1, 0(t6)
	add  t1, t1, -1
	sb   t1, 0(t6)
	j    cont02
print_data:
	li   a7, 64
	li   a0, 1
	move a1, t6
	li   a2, 1
	ecall
	j cont02
read_data:
	li   a7, 63
	li   a0, 0
	move a1, t6
	li   a2, 1
	ecall	             # Fallback en cont02
cont02:
	add  t2, t2, 1       # Incrementa contador del programa
	blt  t2, t3, bucle02 # Mientras no alcancemos el final, repetimos
exit:
	li   a7, 93          # Exit	
	li   a0, 0
	ecall
	
	.bss
mem: 	.space MEM_SIZE
