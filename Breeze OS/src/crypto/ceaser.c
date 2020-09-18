//Ceaser cipher

/*
*   Don't pass in rand() as a key, unless you saved that value specifically. Even then, it would be alot of unnecessary stress on the CPU, refrain to a max of 24. 
*/

//shift is the key, and tells the function how many letters to shift.
char* cipher(char plain[], int cipher_key)
{
    if (cipher_key > 24)
        return "Keysize may be no more than 24.";
    for (int i = 0; (i < 100 && plain[i] != '\0'); i++)
    {
        plain[i] = plain[i] + cipher_key;
    }
    return plain;
}

char* decipher(char cipher[], int decipher_key)
{
    if (decipher_key > 24)
        return "Keysize may be no more than 24.";
    for (int i = 0; (i < 100 && cipher[i] != '\0'); i++)
    {
        cipher[i] = cipher[i] - decipher_key;
    }
    return cipher;
}
