#include <iostream>
#include <openssl/evp.h>
#include <cstdio>

using namespace std;

string md5(const string& content)
{
  EVP_MD_CTX*   context = EVP_MD_CTX_new();
  const EVP_MD* md = EVP_md5();
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int  md_len;
  string        output;

  EVP_DigestInit_ex2(context, md, NULL);
  EVP_DigestUpdate(context, content.c_str(), content.length());
  EVP_DigestFinal_ex(context, md_value, &md_len);
  EVP_MD_CTX_free(context);

  output.resize(md_len * 2);

  for (unsigned int i = 0 ; i < md_len ; ++i)
    std::sprintf(&output[i * 2], "%02x", md_value[i]);

  return output;
}

int main()
{
    string base = "yzbqklnj";
    long chosen_number = -1;
    string result = "";

    //PART2 - start with 6 zeroes
    while(result == "" || result.substr(0, 6) != "000000")
    {
        chosen_number++;
        string md5_input = base + to_string(chosen_number);
        result = md5(md5_input);
    }

    cout << "Result is: " << result << endl;
    cout << "Choosen number is: " << chosen_number << endl;

    return 0;
}
