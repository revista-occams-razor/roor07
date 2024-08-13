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
#include <openssl/rsa.h>
#include <openssl/pem.h>


int main () {
  EVP_PKEY_CTX *ctx;
  EVP_PKEY     *pkey;

  ctx = EVP_PKEY_CTX_new_id (EVP_PKEY_RSA, NULL);
  EVP_PKEY_keygen_init (ctx);
  EVP_PKEY_CTX_set_rsa_keygen_bits (ctx, 2048);
  EVP_PKEY_keygen (ctx, &pkey);
  printf ("Public key:\n");
  
  EVP_PKEY_print_public_fp (stdout, pkey,0, NULL);
  printf ("------------------------------------\n");
  printf ("Private key:\n");
  EVP_PKEY_print_private_fp (stdout, pkey,0, NULL);
  printf ("------------------------------------\n");
  FILE *f = fopen ("example.pem", "wb");
  PEM_write_PrivateKey (f, pkey, NULL, NULL, 0, NULL, NULL);
  fclose (f);
  f = fopen ("example_public.pem", "w");
  PEM_write_PUBKEY (f, pkey);
  fclose (f);
  
}
