/*
* This program is part of Occam's Razor Number 7
* Copyright (C) 2024 Occam's Razor
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/decoder.h>
#include <openssl/core_names.h>
#include <openssl/pem.h>


#include <openssl/aes.h>
#include <openssl/rand.h>

#include <stdio.h>
#include <string.h>

const unsigned char *clave_pub_str =
  "-----BEGIN PUBLIC KEY-----\n"
  "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAu49Qdny7xh2PbeV/oTYr\n"
  "Q9MmkDfKvf/Fgq7DFfAnYuDiYljM/FNCjKRRQLn4YSyINWuXpDAO9AG7jBfVvm2K\n"
  "5Pchkj0HA/Gau9eSFUSoR0LWCrAlAZw8ovq8urQHsFKtd5kkjGsEfnp9zHfvV3NB\n"
  "gO5WzJhhDTnCza5B7AhVKXjS0YeGzKonGhTW6OJTEAnE+oyZp7acdOKy9knXs/Uk\n"
  "2PfRI+P4i/XR09LbQFb06y66MN+CLkm3TVU+Olw6wuSUCj/0rM3CrbWtAbDff9lp\n"
  "vlnHI+A3kOHydm71L1bLDs6fY8kASbA+1OITcmCXPXLLe6omSfRPYkstCU/CoPfb\n"
  "7QIDAQAB\n"
  "-----END PUBLIC KEY-----\n";


int main (int argc, char *argv[]) {
  OSSL_LIB_CTX *libctx = NULL;
  
  /* Generar Claves */
  OSSL_DECODER_CTX *dctx = NULL;
  EVP_PKEY_CTX     *pkctx = NULL;
  EVP_PKEY         *pub_key = NULL;
  EVP_PKEY         *priv_key = NULL;
  
  libctx = NULL; /* Usa el contexto de librería por defecto */
  
  /* lee clave privada usuario 1*/
  dctx = OSSL_DECODER_CTX_new_for_pkey (&priv_key, NULL, NULL, NULL,
					EVP_PKEY_KEYPAIR,libctx, NULL);

  /* Lee clave publica usuario 2*/
  FILE *f = fopen ("example.pem", "rb");
  OSSL_DECODER_from_fp (dctx, f);
  fclose (f);
  OSSL_DECODER_CTX_free (dctx);
  
  dctx = OSSL_DECODER_CTX_new_for_pkey (&pub_key, "PEM", NULL, "RSA",
					EVP_PKEY_PUBLIC_KEY,libctx, NULL);
  
  // Ejemplo leer clave de buffer en memoria
  const unsigned char *data     = clave_pub_str;
  size_t               data_len = strlen (clave_pub_str);;
  
  OSSL_DECODER_from_data (dctx, &data, &data_len);

  
  OSSL_DECODER_CTX_free(dctx);
  printf ("Clave publica leida:\n");
  PEM_write_PUBKEY (stdout, pub_key);
  
  /* Cifrar mensaje para usuario dos. Usamos clave publica usuario 2*/
  char    in[1024];
  char    out[1024];
  size_t  in_len, out_len, len;
  
  memset (in,0,1024);
  strcpy (in, "Hola Occam's Razor. Estoy cifrando asimétricamente!\n");
  in_len = strlen (in);
  memset (out, 0, 1024);
  out_len= in_len;
  
  pkctx = EVP_PKEY_CTX_new (pub_key, NULL);
  if ((EVP_PKEY_encrypt_init (pkctx)) <=0) ERR_print_errors_fp (stderr);
  
  // Calcula tamaño necesario para el buffer de salida
  if (EVP_PKEY_encrypt (pkctx, NULL, &out_len, in, in_len) <=0)
    ERR_print_errors_fp (stderr);
  
  printf ("+ Mensaje original: %d bytes. Mensaje salida: %d bytes\n",
	  in_len, out_len);
  // Aquí podemos reservar memoria. Ya sabemos cuanta necesitamos
  // Ahora encrypta de verdad
  if (EVP_PKEY_encrypt (pkctx, out, &out_len, in, in_len)<=0)
    ERR_print_errors_fp (stderr);
  BIO_dump_indent_fp (stdout, out, out_len, 2);
  printf ("\n");

  EVP_PKEY_CTX_free (pkctx);
  
  // Desencrypta el mensaje
  // Borra buffer in
  memset (in, 0, 1024);
  in_len = out_len;

  // Ahora usamos la clave privada
  if (pkctx = EVP_PKEY_CTX_new_from_pkey (libctx, priv_key, NULL))
    ERR_print_errors_fp (stderr);
  
  if (EVP_PKEY_decrypt_init (pkctx) <= 0)
    ERR_print_errors_fp (stderr);
  
  // Calcula tamaño necesario para el buffer de salida 
  if ((EVP_PKEY_decrypt (pkctx, NULL, &in_len, out, out_len) <= 0))
    ERR_print_errors_fp (stderr);
  printf ("+ Mensaje original: %d bytes. Mensaje salida: %d bytes\n",
	  out_len, in_len);

  // Aquí podemos reservar memoria. Ya sabemos cuanta necesitamos
  // Ahora encrypta de verdad
  if ((EVP_PKEY_decrypt (pkctx, in, &in_len, out, out_len)) <= 0) {
    ERR_print_errors_fp (stderr);
  }
  printf ("%d bytes out (%d)\n", in_len, out_len);
  BIO_dump_indent_fp (stdout, in, in_len, 2);
  printf ("\n");

  EVP_PKEY_CTX_free (pkctx);

  OSSL_LIB_CTX_free (libctx); /* Opcional*/
  
}
