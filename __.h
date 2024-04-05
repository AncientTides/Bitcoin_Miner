// Copyright© 2021, 2022 David GradaSupreme. This code belongs to Mr David GradaSupreme

#ifndef _H_
#define _H_

//			HEADERS
#include "include/bin_con.h"
#include "include/json.hpp"
#include <fstream>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include "windows.h"
#include <ctime>
#include <time.h>
#include <cmath>
#include <stdlib.h> // for system calls

//			NAMESPACE(s)
using std::string;
using std::hex;
using std::vector;
using std::ifstream;
using namespace nlohmann;
using std::stringstream;
using std::cout;
using std::endl;
using std::ofstream;

//			PROTOTYPES
// SHA256
string sha256(string input);
string hex_sha256(string input);
string ParseHex(string& s);
string double_Hex_sha256(string input);

// REVERSE, CONVERT, PROCESS
string Xreadfile(string target_file);
string SwapPerRound_2bits(string data);
string SwapBlockHeight(string data);
string HexToDecimal(string singleHex);
string ReverseString(string data);
string Return_As_Given(string data);
string Pad_HexString(string tink);
string Pad_AlphaSIZE_INT3HEX(uint32_t value);
string ConvertToString(string num);
string BigToLittleAlphabets(string data);
string IntegerToHex(uint32_t num);
string GETLittleEndian_BlockHeight( uint32_t bHeight);
string ConvertStringToHex(string sData);
uint32_t StringTo_32Uint(string x);
string i_ConvertIntToHex(int sData);

string Revert(string _blockdata_);
string HexToBytes(string hex);
string IntegerToHex_64(uint64_t num);



// JSON DATA SERIALIZATION
void GETBLOCKTEMPLETE();
string Get_String_MINTIME();// minimum unix time allowed for block timestamp as string
uint32_t Get_Numeric_MINTIME();// minimum unix time allowed for block timestamp as uint32
string Get_CURRENT_BLOCK_BITS();// current bits in hex format
uint32_t Get_BLOCK_HEIGHT_asInteger();// current block height as uint32
string Get_BLOCK_HEIGHT_asString();// current block height as string
string Get_HASH_TARGET();// current network target
string Get_PREVIOUS_BLOCK_HASH();// current previos block hash
string Get_Version();// blockchain version
uint32_t Get_Numeric_Version();


// BLOCK SUBMISSION
string AppendAllRawTransactions(); // This will be appended to the file holding coinbaseraw data
string createRawTx();
string Transform_String_To_Double(); // convert satoshi unit to btc unit
string Get_TotalFees();
string No_Of_Txs();
vector<string> Get_TransactionVector();

// COINBASE TRANSACTION CREATION
string ScriptSigParser(string coinbase_data, string blockHEIGHT, string X_Data); // 
string Data_Parser(int starting_point, int range, string StringData); // 
string MKccx(string coinbase_hash, vector<string> &v);
string COINBASETX_TX(string coinbase_data, string blockHEIGHT, string X_Data);
// string Coinbase_Generation();

// SYSTEM CALLS
void RunCommand_With_Output_Without_SYMBOL_Defined(string Command_To_Run, string Output_FileName);
void RunCommand(string Command_To_Run);

// LOGGING AND TIME 
void SubmitFile(string encodedhexdata, string destination);
void DYNAMIC_CreateLogFile(string height, string blockheader, string winningHash, string blockReward);
uint32_t PRE_randNum();
uint32_t randNum(uint32_t k);	// requires a value to determine maximum number generatable

// string _GLOBAL_GLOBAL_RAW_COINBASE_;


//!!------++++++++------!! NOTES !!------++++++++------!!
// Coinbase is constant and hardcoded
// Initial raw transaction is constant and hardcoded
// Loop is set to run for 3 to 5 minutes


string Revert(string _blockdata_)
{
    string aa, bb, cc, dd, ee, ff;
    for (int i = 0; i < 8; i++)
        aa += _blockdata_[i];
    for (int i = 8; i < 72; i++)
        bb += _blockdata_[i];
    for (int i = 72; i < 136; i++)
        cc += _blockdata_[i];
    for (int i = 136; i < 144; i++)
        dd += _blockdata_[i];
    for (int i = 144; i < 152; i++)
        ee += _blockdata_[i];
    for (int i = 152; i < 160; i++)
        ff += _blockdata_[i];
    aa = SwapPerRound_2bits(aa);
    bb = SwapPerRound_2bits(bb);
    cc = SwapPerRound_2bits(cc);
    dd = SwapPerRound_2bits(dd);
    ee = SwapPerRound_2bits(ee);
    ff = SwapPerRound_2bits(ff);
    _blockdata_ = aa + bb + cc + dd + ee + ff;
    return _blockdata_;
}


// Copyright© 2021 David GradaSupreme. This code belongs to Mr David GradaSupreme

//			DEFINITIONS OF FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SHA256
/////////////////////////////////////////////////////////////////////////////////////////////////////////


std::string ParseHex(std::string& s)
{
    assert(s.size() % 2 == 0);
    static const std::size_t symbol_count = 256;
    static const unsigned char hex_to_bin[symbol_count] = 
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x00 - 0x07
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x08 - 0x0F
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x10 - 0x17
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x18 - 0x1F
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x20 - 0x27
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x28 - 0x2F
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 0x30 - 0x37
        0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x38 - 0x3F
        0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, // 0x40 - 0x47
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x48 - 0x4F
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x50 - 0x57
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x58 - 0x5F
        0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, // 0x60 - 0x67
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x68 - 0x6F
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x70 - 0x77
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x78 - 0x7F
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x80 - 0x87
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x88 - 0x8F
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x90 - 0x97
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x98 - 0x9F
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xA0 - 0xA7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xA8 - 0xAF
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xB0 - 0xB7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xB8 - 0xBF
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xC0 - 0xC7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xC8 - 0xCF
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xD0 - 0xD7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xD8 - 0xDF
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xE0 - 0xE7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xE8 - 0xEF
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xF0 - 0xF7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 0xF8 - 0xFF
    };

    std::string out;
    auto itr = s.begin();
    while (itr != s.end())
    {
       unsigned char b = static_cast<unsigned char>(hex_to_bin[*(itr++)] << 4);
       b |= static_cast<unsigned char>(hex_to_bin[*(itr++)]     );
       out.push_back(b);
    }
    return out;
}

//      ----------------        SHA256 ALGORITHM        ------------------

typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned long long uint64;

static const unsigned int SHA224_256_BLOCK_SIZE = (64); //(512/8);
void init();
// void transform_T(const unsigned char *message, unsigned int block_nb);
void update(const unsigned char *message, unsigned int len);
void final(unsigned char *digest);
static const unsigned int DIGEST_SIZE = (32);

void transform(const unsigned char *message, unsigned int block_nb);
unsigned int m_tot_len;
unsigned int m_len;
unsigned char m_block[2*SHA224_256_BLOCK_SIZE];
uint32 m_h[8];

#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA256_F1(x) (SHA2_ROTR(x,  2) ^ SHA2_ROTR(x, 13) ^ SHA2_ROTR(x, 22))
#define SHA256_F2(x) (SHA2_ROTR(x,  6) ^ SHA2_ROTR(x, 11) ^ SHA2_ROTR(x, 25))
#define SHA256_F3(x) (SHA2_ROTR(x,  7) ^ SHA2_ROTR(x, 18) ^ SHA2_SHFR(x,  3))
#define SHA256_F4(x) (SHA2_ROTR(x, 17) ^ SHA2_ROTR(x, 19) ^ SHA2_SHFR(x, 10))
#define SHA2_UNPACK32(x, str)                 \
{                                             \
    *((str) + 3) = (uint8) ((x)      );       \
    *((str) + 2) = (uint8) ((x) >>  8);       \
    *((str) + 1) = (uint8) ((x) >> 16);       \
    *((str) + 0) = (uint8) ((x) >> 24);       \
}
#define SHA2_PACK32(str, x)                   \
{                                             \
    *(x) =   ((uint32_t) *((str) + 3)      )    \
           | ((uint32_t) *((str) + 2) <<  8)    \
           | ((uint32_t) *((str) + 1) << 16)    \
           | ((uint32_t) *((str) + 0) << 24);   \
}

//          ---------------      DEFINITIONS ARC        --------------------------
//UL = uint32
const unsigned int sha256_k[64] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void transform(const unsigned char *message, unsigned int block_nb)
{
    uint32_t w[64]; // 64
    uint32_t wv[8];
    uint32_t t1, t2;
    const unsigned char *sub_block;
    for (int i = 0; i < (int) block_nb; i++)
    {
        sub_block = message + (i << 6);

        for (int j = 0; j < 16; j++) // 16
            SHA2_PACK32(&sub_block[j << 2], &w[j]);

        for (int x = 16; x < 64; x++) // 64
            w[x] =  SHA256_F4(w[x -  2]) + w[x -  7] + SHA256_F3(w[x - 15]) + w[x - 16];

        for (int d = 0; d < 8; d++) // 8
            wv[d] = m_h[d];

        for (int h = 0; h < 64; h++) // 64
        {
            t1 = wv[7] + SHA256_F2(wv[4]) + SHA2_CH(wv[4], wv[5], wv[6]) + sha256_k[h] + w[h];
            t2 = SHA256_F1(wv[0]) + SHA2_MAJ(wv[0], wv[1], wv[2]);
            wv[7] = wv[6];
            wv[6] = wv[5];
            wv[5] = wv[4];
            wv[4] = wv[3] + t1;
            wv[3] = wv[2];
            wv[2] = wv[1];
            wv[1] = wv[0];
            wv[0] = t1 + t2;
        }
        for (int q = 0; q < 8; q++) // 8
            m_h[q] += wv[q];
    }
}


void init()
{
    m_h[0] = 0x6a09e667;
    m_h[1] = 0xbb67ae85;
    m_h[2] = 0x3c6ef372;
    m_h[3] = 0xa54ff53a;
    m_h[4] = 0x510e527f;
    m_h[5] = 0x9b05688c;
    m_h[6] = 0x1f83d9ab;
    m_h[7] = 0x5be0cd19;
    m_len = 0;
    m_tot_len = 0;
}


void update(const unsigned char *message, unsigned int len)
{
    unsigned int block_nb;
    unsigned int new_len, rem_len, tmp_len;
    const unsigned char *shifted_message;
    tmp_len = SHA224_256_BLOCK_SIZE - m_len;
    rem_len = len < tmp_len ? len : tmp_len;
    memcpy(&m_block[m_len], message, rem_len);

    if (m_len + len < SHA224_256_BLOCK_SIZE)
    {
        m_len += len;
        return;
    }

    new_len = len - rem_len;
    block_nb = new_len / SHA224_256_BLOCK_SIZE;
    shifted_message = message + rem_len;
    transform(m_block, 1);
    transform(shifted_message, block_nb);
    rem_len = new_len % SHA224_256_BLOCK_SIZE;
    memcpy(m_block, &shifted_message[block_nb << 6], rem_len);
    m_len = rem_len;
    m_tot_len += (block_nb + 1) << 6;
}

void final(unsigned char *digest)
{
    unsigned int block_nb;
    unsigned int pm_len;
    unsigned int len_b;
    block_nb = (1 + ((SHA224_256_BLOCK_SIZE - 9) < (m_len % SHA224_256_BLOCK_SIZE)));
    len_b = (m_tot_len + m_len) << 3;
    pm_len = block_nb << 6;
    memset(m_block + m_len, 0, pm_len - m_len);
    m_block[m_len] = 0x80;
    SHA2_UNPACK32(len_b, m_block + pm_len - 4);
    transform(m_block, block_nb);

    for (int f = 0 ; f < 8; f++)
        SHA2_UNPACK32(m_h[f], &digest[f << 2]);
}



std::string sha256(std::string input)
{
    unsigned char digest[32];
    memset(digest,0,32);
   
    init();
    update( (unsigned char*)input.c_str(), input.length());
    final(digest);

    char buf[2*32+1];
    buf[2*32] = 0;
    for (int i = 0; i < 32; i++)
        sprintf(buf+i*2, "%02x", digest[i]);
    return std::string(buf);
}


std::string hex_sha256(std::string input)
{    
    unsigned char hash[32];// header_data is "160" in size because midstate optimization is not implemented
    char buf[2*32+1];
    buf[2*32] = 0;

    input = ParseHex(input); // ParseHex() is UNDEFINED !!!
    init(); // Initiialize
    update((unsigned char*)input.c_str(), input.length()); // Update
    final(hash); // Finalize

    // Uncomment code below if you want to directly double hash input data using a single "sha256(input)" function call
    // init();
    // update(hash, 32);
    // final(hash);

    for (int i = 0; i < 32; i++) 
        sprintf(buf+i*2, "%02x", hash[i]); // feed data from hash into buf and format data

    return std::string(buf); // Return buf as string instead of char
}



std::string double_Hex_sha256(std::string input)
{    
    unsigned char hash[32];// header_data is "160" in size because midstate optimization is not implemented
    char buf[2*32+1];
    buf[2*32] = 0;

    input = ParseHex(input); // ParseHex() is UNDEFINED !!!
    init(); // Initiialize
    update((unsigned char*)input.c_str(), input.length()); // Update
    final(hash); // Finalize

    // Uncomment code below if you want to directly double hash input data using a single "sha256(input)" function call
    init();
    update(hash, 32);
    final(hash);

    for (int i = 0; i < 32; i++) 
        sprintf(buf+i*2, "%02x", hash[i]); // feed data from hash into buf and format data

    return std::string(buf); // Return buf as string instead of char
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	REVERSE, CONVERT, PROCESS
/////////////////////////////////////////////////////////////////////////////////////////////////////////

string Xreadfile(string target_file)
{
	string myText, kkk; // Create string to hold output data
	ifstream MyReadFile(target_file); // Read from the text file
	while (getline(MyReadFile, myText))	// Use a while loop together with the getline() function to read the file line by line
		kkk += myText; // Output the text from the file
	MyReadFile.close(); // Close the file
	return kkk;
} // Sucessfully compiled on the 20/01/2022 12:30:53 PM __-__ Edited on 26/01/22 03:30PM


string Pad_AlphaSIZE_INT3HEX(uint32_t value)
{
    string f = Pad_HexString(IntegerToHex(value));
	return f;
}

string Pad_HexString(string tink)
{
	if (tink.length() == 1)
		tink = "0000000" + tink;
	else if (tink.length() == 2)
		tink = "000000" + tink;
	else if (tink.length() == 3)
		tink = "00000" + tink;
	else if (tink.length() == 4)
		tink = "0000" + tink;
	else if (tink.length() == 5)
		tink = "000" + tink;
	else if (tink.length() == 6)
		tink = "00" + tink;
	else if (tink.length() == 7)
		tink = "0" + tink;
	else if (tink.length() == 8)
		return tink;
    else if (tink.length()>8 && tink.length()<50)
        return tink;
	return tink;
}

string ConvertStringToHex(string sData)
{
	string new_SData;
	char Temp[1000];
	sprintf(Temp, "%x", sData);
	stringstream aa;aa << Temp;aa >> new_SData;aa.clear();
	return new_SData;
}

string GETLittleEndian_BlockHeight(uint32_t bHeight)
{
	string reversedDATA;
	char i[25];
	sprintf(i, "%x", bHeight);
	stringstream aa;aa << i;aa >> reversedDATA;aa.clear();
	reversedDATA = SwapBlockHeight(reversedDATA);
	return reversedDATA;
}

string BigToLittleAlphabets(string data)
{
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] == 'A')
			data[i] = 'a';
		else if (data[i] == 'B')
			data[i] = 'b';
		else if (data[i] == 'C')
			data[i] = 'c';
		else if (data[i] == 'D')
			data[i] = 'd';
		else if (data[i] == 'E')
			data[i] = 'e';
		else if (data[i] == 'F')
			data[i] = 'f';
	}
	return data;
}

string ConvertToString(string num)
{
	string stringFormat;
	stringstream to_Str;
	to_Str << num;
	to_Str >> stringFormat;
    to_Str.clear();
	return stringFormat;
}

string IntegerToHex(uint32_t num)
{
	vector<char> arr;
	string cache;
	int i = 0;
    if (num == 0)
    {
        stringstream cs;cs << num;cs >> cache;cs.clear();
        return cache;
    }
	while(num != 0) 
	{
		int temp = 0;
		temp = num % 16;
		if(temp < 10)
		{
			arr.push_back(temp + 48);
			i++;
		} 
		else 
		{
			arr.push_back(temp + 55);
			i++;
		}
		num = num/16;
	}
	for(int j = i-1; j >= 0; j--)
		cache+= arr[j];
	return BigToLittleAlphabets(cache);
}




string ReverseString(string data)
{
	string data_var;
	int count;
	count = data.length() - 1 ;
	while (count >= 0)
	{
		data_var = data_var + data[count] ;
		count--;
	}
	return data_var;
}




string Return_As_Given(string data)
{
	string bits; // global return variable
	string byte1, byte2, byte3, byte4;
	byte4 = data.substr(6, 2);
	byte3 = data.substr(4, 2);
	byte2 = data.substr(2, 2);
	byte1 = data.substr(0, 2);
	bits = byte1 + byte2 + byte3 + byte4;
	return bits;
}

string Return_CREATERAWTRANSACTION_OUTPUT_As_Given(string data)
{
	string bits; // global return variable
	for (int i = 0; i < data.length(); i++)
		bits += data[i];
	return bits;
}


string SwapBlockHeight(string data)
{
	string bits = SwapPerRound_2bits(data);
	return bits;
}



string Swap_2bits(string data) // SWAP ENDAINESS
{
    vector<string> t1;
    string bits; // global return variable

    for (int i = 0; i < data.length()+2; i+=2)
        t1.push_back(data.substr(i, 2));

    for (int b = 0; b < t1.size()+1; ++b)
        bits += t1[t1.size()-b];
    return bits;
}

string i_ConvertIntToHex(int sData)
{
    string new_SData;
    char Temp[1000];
    sprintf(Temp, "%x", sData);
    stringstream aa;
    aa << Temp;
    aa >> new_SData;
    aa.clear();
    return new_SData;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	JSON DATA SERIALIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////


void GETBLOCKTEMPLATE()
{// getblocktemplate '{"rules": ["segwit"]}' // 03:20 AM 19/01/2022 -- Correct syntax! for Bitcoin Core GUI
    string getblocktemplate_syntax = "cd \"C:\\Users\\Ancient Tides\\Desktop\\__\\bat_files\" && call gt.bat";
    string distribute_template = "cd \"C:\\Users\\Ancient Tides\\Desktop\\__\\bat_files\" && call distribute.bat";
    string filename = "getblocktemplate_Response.json"; // Create file Name
    RunCommand_With_Output_Without_SYMBOL_Defined(getblocktemplate_syntax, filename); // create json file with getblockresponse output
    RunCommand(distribute_template);// Distribute template to al miners
} // Successfuly compiled on 31/01/2022 11:30AM


string Get_Version()
{
	stringstream jj;
	string request;
	uint32_t f;
	ifstream file_input("bat_files\\getblocktemplate_Response.json");
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	f = object.at("version");
	jj << f;
	jj >> request;
    jj.clear();
	return request;
}




uint32_t Get_Numeric_Version()
{
    uint32_t f;
    ifstream file_input("bat_files\\getblocktemplate_Response.json");
    json object = json::parse(file_input); // Parse json data
    file_input.close(); // close streamer
    f = object.at("version");
    return f;
}


string Get_PREVIOUS_BLOCK_HASH()
{
	string request;
	ifstream file_input("bat_files\\getblocktemplate_Response.json");
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	request = object.at("previousblockhash");
	return request;
}


string Get_HASH_TARGET()
{
	string request;
	ifstream file_input("bat_files\\getblocktemplate_Response.json");
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	request = object.at("target");
	return request;
}


string Get_BLOCK_HEIGHT_asString()
{
	stringstream jj;
	string request;
	uint32_t f;
	ifstream file_input("bat_files\\getblocktemplate_Response.json");
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	f = object.at("height");
	jj << f;
	jj >> request;
    jj.clear();
	return request;
}


uint32_t Get_BLOCK_HEIGHT_asInteger()
{
	uint32_t f;
	ifstream file_input("bat_files\\getblocktemplate_Response.json");
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	f = object.at("height");
	return f;
}


string Get_CURRENT_BLOCK_BITS()
{
	string request;
	ifstream file_input("bat_files\\getblocktemplate_Response.json");
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	request = object.at("bits");
	return request;
}



uint32_t Get_Numeric_MINTIME()
{
	uint32_t request;
	ifstream file_input("bat_files\\getblocktemplate_Response.json");
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	request = object.at("mintime");
	return request;
}


string Get_String_MINTIME()
{
	stringstream jj;
	string request;
	uint32_t f;
	ifstream file_input("bat_files\\getblocktemplate_Response.json");
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	f = object.at("mintime");
	jj << f;
	jj >> request;
    jj.clear();
	return request;
}



vector<string> Get_TransactionVector()
{
    ifstream file_input("bat_files\\getblocktemplate_Response.json");
    json object = json::parse(file_input); // Parse json data
    file_input.close(); // close streamer
    vector<string> Txid_Retreiver; // 
    auto &Array_Txid = object["transactions"]; // Create object pointing to 'transactions' array
    for(auto &target : Array_Txid) // Traverse through transaction array
        Txid_Retreiver.push_back(target["txid"].get<string>());

    return Txid_Retreiver;
}


string Get_CoinbaseValue()
{
    stringstream jj;
    string request;
    uint32_t f;
    ifstream file_input("bat_files\\getblocktemplate_Response.json");
    json object = json::parse(file_input); // Parse json data
    file_input.close(); // close streamer
    f = object.at("coinbasevalue");
    jj << f;
    jj >> request;
    jj.clear();
    return request;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  BLOCK SUBMISSION
/////////////////////////////////////////////////////////////////////////////////////////////////////////

string BlockReward(uint32_t blockHeight)
{
    string blockReward;
    if ((blockHeight >= 630000) && (blockHeight < 840000))
    {
        blockReward = "6.25000000";
        return blockReward;
    }
    else if ((blockHeight >= 840000) && (blockHeight < 1050000))
    {
        blockReward = "3.12500000";
        return blockReward;
    }
    else if ((blockHeight >= 1050000) && (blockHeight < 1260000))
    {
        blockReward = "1.56250000";
        return blockReward;
    }
    else if ((blockHeight >= 1260000) && (blockHeight >= 1470000))
    {
        blockReward = "0.78125000";
        return blockReward;
    }
    else if ((blockHeight >= 1470000) && (blockHeight < 1680000))
    {
        blockReward = "0.39062500";
        return blockReward;
    }
    else if ((blockHeight >= 1680000) && (blockHeight < 1890000))
    {
        blockReward = "0.19531250";
        return blockReward;
    }
    else if ((blockHeight >= 1890000) && (blockHeight < 2100000))
    {
        blockReward = "0.09765625";
        return blockReward;
    }
    else if ((blockHeight >= 2100000) && (blockHeight < 2310000))
    {
     blockReward = "0.04882812";
     return blockReward;
    }
}


string No_Of_Txs()
{
    ifstream file_input("bat_files\\getblocktemplate_Response.json");
    json object = json::parse(file_input); // Parse json data
    file_input.close(); // close streamer

    vector<string> RawData_Retreiver; // vector for holding raw transaction script
    // RETRIEVE TXID FROM JSON FILE
    auto &Array_Data = object["transactions"]; // Create object pointing to 'transactions' array
    for(auto &d_target : Array_Data) // Traverse through transaction array
        RawData_Retreiver.push_back(d_target["data"].get<std::string>());
    // DATA FROM JSON FILE HAS BEEN RETRIEVED
    int calc_num_of_transactions = RawData_Retreiver.size() + 1; // number of transactions + coinbase transaction
    string numOfTransactions = IntegerToHex(calc_num_of_transactions);// variable for hex num of transactions

    return numOfTransactions;
}


string AppendAllRawTransactions() // This will be appended to the file holding coinbaseraw data
{
    vector<string> RawData_Retreiver; // vector for holding raw transaction script
    string combined_rawData, pre_buffer;

    // Scan json data to json serializatoin object
    ifstream file_input("getblocktemplate_Response.json");
    json object = json::parse(file_input); // Parse json data
    file_input.close(); // close streamer

    // get raw transaction data for later submissions
    auto &Array_Data = object["transactions"]; // Create object pointing to 'transactions' array
    for(auto &d_target : Array_Data) // Traverse through transaction array
        RawData_Retreiver.push_back(d_target["data"].get<std::string>());

    // concatenate all retrieved raw data
    for (int i = 0; i < RawData_Retreiver.size(); i++)
        pre_buffer += RawData_Retreiver[i]; //concatenate all raw transactions into a string
    // if string cannot hold all data at once, divide concatenatoin of raw data into partitions

    combined_rawData = Return_CREATERAWTRANSACTION_OUTPUT_As_Given(pre_buffer); // Eliminate extra bytes

    return combined_rawData;
}



// string Get_TotalFees(uint32_t No_Of_Txids_Used_In_Merkle)

string Get_TotalFees()
{
    string stringReward = BlockReward(Get_BLOCK_HEIGHT_asInteger());
    string fim_string;
    // uint32_t T_Fees = TotalFeesInCandidateBlock();
    uint32_t fees_in_Merkle, COINBASE_BLOCK_REWARD_BASED_ON_HEIGHT;
    stringstream ww;
    ww << stringReward;
    ww >> COINBASE_BLOCK_REWARD_BASED_ON_HEIGHT;
    ww.clear();

    ifstream file_input("bat_files\\getblocktemplete_Response.json");
    json object = json::parse(file_input); // Parse json data
    file_input.close(); // close streamer
    vector<uint32_t> fees_per_T; // 
    auto &Array_fees = object["transactions"]; // Create object pointing to 'transactions' array
    for(auto &target : Array_fees) // Traverse through transaction array
        fees_per_T.push_back(target["fee"].get<uint32_t>());
    

    for (uint32_t i = 0; i < fees_per_T[Get_TransactionVector().size()]; i++)
        fees_in_Merkle += fees_per_T[i]; // Calculate fees based on merkle txid passed via argument

    fees_in_Merkle = fees_in_Merkle + COINBASE_BLOCK_REWARD_BASED_ON_HEIGHT;
    
    stringstream jj;
    jj << fees_in_Merkle;
    jj >> fim_string;
    jj.clear();
    return fim_string;

    // return fees_in_Merkle; // return value of actual transactions mined
}


string Transform_String_To_Double()// convert satoshi unit to btc unit
{
    string tempest, input = Get_TotalFees();
    for (int i = 0; i <= input.length()-1; i++)
    {
        tempest += input[i];
        if (i==(input.length()-input.length()))
            tempest += '.';
    }
    return tempest;
} // Sucessfully compiled on the 20/01/2022 02:06:22 AM



// creatw raw tx batch file needs the value hence, value must be saved to a txt file and sleep for 1 second before continuing to retreive data and create dynamic rawcoinbasetx that includes all tx fees + coinbase reward

string createRawTx()
{
    // Store maximum profit == coinbase reward + transaction fees into max_earnings.txt as a double data type
    string filename = "create_transaction\\max_earnings.txt";    // Create filename
    string fee = Transform_String_To_Double();
    ofstream File(filename);   // Create and open a text file
    File << fee;
    File.close(); // close file

    // call batch to create raw tx string
    string createRawTx_Syntax = "cd \"C:\\Users\\Ancient Tides\\Desktop\\__\\create_transaction\" && call createrawtransaction.bat";
    RunCommand(createRawTx_Syntax); // create json file with rawcoinbaseTX output

    // stream string from RAW_TX.txt into variable TX_RETRIEVED
    string TX_RETRIEVED = "";
    ifstream raw_data("raw_coinbase_tx.txt"); // read from data
    while (raw_data)
        getline(raw_data, TX_RETRIEVED);
    raw_data.close(); // close streamer
    // ensure that no invalid byte data corrupts rawtx data
    TX_RETRIEVED = Return_CREATERAWTRANSACTION_OUTPUT_As_Given(TX_RETRIEVED);

    // return raw transaction data to scriptsig
    return TX_RETRIEVED;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	COINBASE TRANSACTION CREATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////

string MKccx(string coinbase_hash, vector<string> v)
{
    string hash;
    string temp1;
    int x = 0, d = 0;
    vector<string> calculate_tx;
    calculate_tx[0] = coinbase_hash; // Store swapped endian format of coinbase hash in new vector index 0

    if (v.empty())
        return coinbase_hash;
    else if (v.size() == 1)
    {
        hash = v[0];
        return hash;
    }

    for (int d = 0; d < v.size(); d++)
        calculate_tx[1+d] = SwapPerRound_2bits(v[d]);

    // for(int i = 0; i < v.size(); i++) // Swap 2 bytes and reverse order of all txid's within transactions array
    //     v[i] = SwapPerRound_2bits(v[i]);

    while(true)
    {
        int z = 0;
        if (calculate_tx.size()%2 == 1) // IF SIZE OF VECTOR % 2 == 1
        {
            temp1 = calculate_tx[calculate_tx.size()-1]; // STORE VALUE OF LAST VECTOR INDEX TO TEMP1
            calculate_tx.push_back(temp1); // ADD THAT VALUE INTO VECTOR
            for(int i = 0, z = i+1; i < calculate_tx.size(); i+=2)
            {
                hash = calculate_tx[i] + calculate_tx[z]; // Concatenate txid pairs together
                hash = double_Hex_sha256(hash); // DoubleHash concatenated txid's
                // cout <<"hash "<<calculate_tx[i]<<" and hash "<<calculate_tx[z]<<" concatenated & double hashed is : "<<hash<<"\n \n";
                calculate_tx.push_back(hash);
                z+=2;
            }

            for (int i = 0; i < calculate_tx.size(); i++)
            {
                temp1 = calculate_tx[i];
                calculate_tx[i] = temp1;
                // std::cout << "calculate_tx index " << i << " is " << calculate_tx[i] << "\n \n";
            }
            calculate_tx.resize(calculate_tx.size());
            // cout << "NEW SIZE OF V AFTER COLLECTING ELEMENTS FROM calculate_tx IS " << calculate_tx.size() << "\n\n\n";

            if (calculate_tx.size() == 2)
            {
                hash = calculate_tx[0] + calculate_tx[1];
                // cout <<"Final hashes are "<< calculate_tx[0] <<" and "<< calculate_tx[1] <<"\n \n";
                hash = double_Hex_sha256(hash);
                
                hash = SwapPerRound_2bits(hash);
                // cout <<"Reversed hash of final concatenation is | "<< hash <<"\n \n";
                return hash;
            }
            calculate_tx.clear();
        }
        else if (calculate_tx.size()%2 == 0) // IF SIZE OF VECTOR % 2 == 0
        {
            for(int i = 0, z = i+1; i < calculate_tx.size(); i+=2)
            {
                hash = calculate_tx[i] + calculate_tx[z]; // Concatenate txid pairs together
                hash = double_Hex_sha256(hash); // DoubleHash concatenated txid's
                // cout <<"hash "<<calculate_tx[i]<<" and hash "<<calculate_tx[z]<<" concatenated & double hashed is : "<<hash<<"\n \n";
                calculate_tx.push_back(hash);
                z+=2;
            }

            for (int i = 0; i < calculate_tx.size(); i++)
            {
                temp1 = calculate_tx[i];
                calculate_tx[i] = temp1;
                // std::cout << "calculate_tx index " << i << " is " << calculate_tx[i] << "\n \n";
            }
            calculate_tx.resize(calculate_tx.size());
            // cout << "NEW SIZE OF V AFTER COLLECTING ELEMENTS FROM calculate_tx IS " << calculate_tx.size() << "\n\n\n";

            if (calculate_tx.size() == 2)
            {
                hash = calculate_tx[0] + calculate_tx[1];
                // cout <<"Final hashes are "<< calculate_tx[0] <<" and "<< calculate_tx[1] <<"\n \n";
                hash = double_Hex_sha256(hash);
                
                hash = SwapPerRound_2bits(hash);
                // cout <<"Reversed hash of final concatenation is | "<< hash <<"\n \n";
                return hash;
            }
            calculate_tx.clear();
        }       
    }
}// Successful compilation on 06/02/2022



// string Coinbase_Generation()
// {//	Create COINBASE Transaction, add its hash to transaction array, calculate merkle root
// 	string BLOCK_HEIGHT = Get_BLOCK_HEIGHT_asString();
	
// 	// PARSE INPUTS FROM JSON DATA
// 	string bitcoin_cli_Parser_Response = ""; // stores response and passes it to scriptsig parser to parse raw data and correct inputs & output
	
//     string coinbase = IntegerToHex_64(randNum_64(777444555999));// generate random number, convert to hexadecimal
//     GLOBAL_COINBASEVALUE = coinbase;
// 	// coinbase = IntegerToHex(StringTo_64Uint(HexToDecimal(coinbase)));/// Generate arbitrary ascii data & convert to hex
// 	// string CreateTransaction_Output = "c_raw_tx_FILE.txt";// Raw transaction file name
// 	string CreateTransaction_Output = "02000000010000000000000000000000000000000000000000000000000000000000000000ffffff7f00ffffffff0140be402500000000160014ab1daa11d746a415607992b2a1673e8ebec78c2d00000000";// Raw transaction file name

// 	// CREATE COINBASE AND ADD TO TRANSACTION VECTOR
// 	// bitcoin_cli_Parser_Response = Xreadfile(CreateTransaction_Output); // store raw transaction into string 
// 	bitcoin_cli_Parser_Response = ScriptSigParser(CreateTransaction_Output, BLOCK_HEIGHT, coinbase); // Call ScriptSigParser to MODIFY RESULTS FROM GETBLOCKTEMPLETE
// 	// coinbase = bitcoin_cli_Parser_Response; // Assign created coinbase hex to new variable

// 	return bitcoin_cli_Parser_Response;
// } // Completion on 24/01/2022 01:28PM


string Data_Parser(int starting_point, int range, string StringData)
{ // requires #include <string>
	string a;
	for (int i = starting_point; i <= range; i++)
		a = a + StringData[i];
	return a;
	//nVersion += BlockHeader[i]; etc...
}



string ScriptSigParser(string coinbase_data, string blockHEIGHT, string X_Data)
{
    // string blockHEIGHT = Get_BLOCK_HEIGHT_asString();
    int tempInt = 0;
    int locktime_denominate = coinbase_data.length() - 8, Data_Size = coinbase_data.length();
    string temptemp = coinbase_data; // temporary storage variable
    string txid, vout, scriptsig_Size, Byte_PUSH, LittleEndian_blockHeight, ArbitraryData, sequence, outputCount,   Hexadecimal_blockReward, scriptPubKey, locktime;

    txid = Data_Parser(0, 73, coinbase_data); // PROVIDED !LENGTH : 74 BYTES
    vout = Data_Parser(74, 81, coinbase_data); // PROVIDED !LENGTH : 8 BYTES
    sequence = Data_Parser(84, 91, coinbase_data); // PROVIDED !LENGTH : 8 BYTES
    outputCount = Data_Parser(92, 93, coinbase_data);  // PROVIDED !LENGTH : 2 BYTES
    Hexadecimal_blockReward = Data_Parser(94, 94+16-1, coinbase_data); // PROVIDED !!! -LENGTH : 16 BYTES
    scriptPubKey = Data_Parser(94+16, locktime_denominate-1, coinbase_data); // PROVIDED !LENGTH : DYNAMIC SIZE OF BYTES
    // locktime = Return_As_Given(Data_Parser(locktime_denominate, Data_Size-1, coinbase_data)); // PROVIDED !LENGTH : 8 BYTES
    locktime = "00000000";// DEFINE LOCKTIME VALUE
    vout = "ffffffff"; // from "ffffff7f" to "ffffffff"
    Byte_PUSH = "03";// SET PUSH HEX 
    LittleEndian_blockHeight = blockHEIGHT;// GENERATE LITTLE ENDIAN FORMATTED BLOCK HEIGHT
    ArbitraryData = X_Data; // Get arbitrary data
    tempInt = Byte_PUSH.length() + LittleEndian_blockHeight.length() + ArbitraryData.length();// CALCULATE SCRIPTSIG SIZE
    scriptsig_Size = i_ConvertIntToHex(tempInt); // convert length of all data to hex format 
    // CONCATENATE PARSED DATA
    coinbase_data = txid + vout + scriptsig_Size + Byte_PUSH + LittleEndian_blockHeight + ArbitraryData + sequence + outputCount +  Hexadecimal_blockReward + scriptPubKey + locktime;
    coinbase_data = double_Hex_sha256(coinbase_data); // Double hash raw coinbase transaction data

    return coinbase_data;// RETURN COINBASE
}


string COINBASETX_TX(string coinbase_data, string blockHEIGHT, string X_Data)
{
    // string blockHEIGHT = Get_BLOCK_HEIGHT_asString();
    int tempInt = 0;
    int locktime_denominate = coinbase_data.length() - 8, Data_Size = coinbase_data.length();
    string temptemp = coinbase_data; // temporary storage variable
    string txid, vout, scriptsig_Size, Byte_PUSH, LittleEndian_blockHeight, ArbitraryData, sequence, outputCount,   Hexadecimal_blockReward, scriptPubKey, locktime;

    txid = Data_Parser(0, 73, coinbase_data); // PROVIDED !LENGTH : 74 BYTES
    vout = Data_Parser(74, 81, coinbase_data); // PROVIDED !LENGTH : 8 BYTES
    sequence = Data_Parser(84, 91, coinbase_data); // PROVIDED !LENGTH : 8 BYTES
    outputCount = Data_Parser(92, 93, coinbase_data);  // PROVIDED !LENGTH : 2 BYTES
    Hexadecimal_blockReward = Data_Parser(94, 94+16-1, coinbase_data); // PROVIDED !!! -LENGTH : 16 BYTES
    scriptPubKey = Data_Parser(94+16, locktime_denominate-1, coinbase_data); // PROVIDED !LENGTH : DYNAMIC SIZE OF BYTES
    // locktime = Return_As_Given(Data_Parser(locktime_denominate, Data_Size-1, coinbase_data)); // PROVIDED !LENGTH : 8 BYTES
    locktime = "00000000";// DEFINE LOCKTIME VALUE
    vout = "ffffffff"; // from "ffffff7f" to "ffffffff"
    Byte_PUSH = "03";// SET PUSH HEX 
    LittleEndian_blockHeight = blockHEIGHT;// GENERATE LITTLE ENDIAN FORMATTED BLOCK HEIGHT
    ArbitraryData = X_Data; // Get arbitrary data
    tempInt = Byte_PUSH.length() + LittleEndian_blockHeight.length() + ArbitraryData.length();// CALCULATE SCRIPTSIG SIZE
    scriptsig_Size = i_ConvertIntToHex(tempInt); // convert length of all data to hex format 
    // CONCATENATE PARSED DATA
    coinbase_data = txid + vout + scriptsig_Size + Byte_PUSH + LittleEndian_blockHeight + ArbitraryData + sequence + outputCount +  Hexadecimal_blockReward + scriptPubKey + locktime;

    return coinbase_data;// RETURN COINBASE
}



// string ScriptSigParser(string coinbase_data, string blockHEIGHT, string X_Data)
// {
// 	coinbase_data = Return_CREATERAWTRANSACTION_OUTPUT_As_Given(coinbase_data); // filter data just case of excess stream bytes
// 	int tempInt = 0;
// 	int locktime_denominate = coinbase_data.length() - 8, Data_Size = coinbase_data.length();
// 	string temptemp = coinbase_data; // temporary storage variable
// 	string txid, vout, scriptsig_Size, Byte_PUSH, LittleEndian_blockHeight, ArbitraryData, sequence, outputCount,	Hexadecimal_blockReward, scriptPubKey, locktime;

// 	txid = Data_Parser(0, 73, coinbase_data); // PROVIDED !LENGTH : 74 BYTES
// 	vout = Data_Parser(74, 81, coinbase_data); // PROVIDED !LENGTH : 8 BYTES
// 	sequence = Data_Parser(84, 91, coinbase_data); // PROVIDED !LENGTH : 8 BYTES
// 	outputCount = Data_Parser(92, 93, coinbase_data);  // PROVIDED !LENGTH : 2 BYTES
// 	Hexadecimal_blockReward = Data_Parser(94, 94+16-1, coinbase_data); // PROVIDED !!! -LENGTH : 16 BYTES
// 	scriptPubKey = Data_Parser(94+16, locktime_denominate-1, coinbase_data); // PROVIDED !LENGTH : DYNAMIC SIZE OF BYTES
// 	// locktime = Return_As_Given(Data_Parser(locktime_denominate, Data_Size-1, coinbase_data)); // PROVIDED !LENGTH : 8 BYTES
// 	locktime = "00000000";// DEFINE LOCKTIME VALUE
// 	vout = "ffffffff"; // from "ffffff7f" to "ffffffff"
// 	Byte_PUSH = "03";// SET PUSH HEX 
// 	LittleEndian_blockHeight = blockHEIGHT;// GENERATE LITTLE ENDIAN FORMATTED BLOCK HEIGHT
// 	ArbitraryData = X_Data; // Get arbitrary data
// 	tempInt = Byte_PUSH.length() + LittleEndian_blockHeight.length() + ArbitraryData.length();// CALCULATE SCRIPTSIG SIZE
// 	scriptsig_Size = i_ConvertIntToHex(tempInt); // convert length of all data to hex format 
// 	// CONCATENATE PARSED DATA
	
//     coinbase_data = txid + vout + scriptsig_Size + Byte_PUSH + LittleEndian_blockHeight + ArbitraryData + sequence + outputCount + Hexadecimal_blockReward + scriptPubKey + locktime;
	
//     _GLOBAL_GLOBAL_RAW_COINBASE_ = coinbase_data; // raw hex encoded coinbase data stored within global variaable


//     // coinbase_data = txid + vout + scriptsig_Size + Byte_PUSH + LittleEndian_blockHeight + sequence + outputCount +  Hexadecimal_blockReward + scriptPubKey + locktime;
//     coinbase_data = double_Hex_sha256(coinbase_data);// THEN DOUBLE HASH STRING TO CREATE COINBASE DATA.
// 	return coinbase_data;// RETURN COINBASE
// }// Successfully compiled on 20/01/2022 at 01:40AM



// string RawCoinbaseData()
// {
//     string coinbase_data = "02000000010000000000000000000000000000000000000000000000000000000000000000ffffff7f00ffffffff0140be402500000000160014ab1daa11d746a415607992b2a1673e8ebec78c2d00000000";
//     string blockHEIGHT = Get_BLOCK_HEIGHT_asString();
//     string X_Data = GLOBAL_COINBASEVALUE;
//     int tempInt = 0;
//     int locktime_denominate = coinbase_data.length() - 8, Data_Size = coinbase_data.length();
//     string temptemp = coinbase_data; // temporary storage variable
//     string txid, vout, scriptsig_Size, Byte_PUSH, LittleEndian_blockHeight, ArbitraryData, sequence, outputCount,   Hexadecimal_blockReward, scriptPubKey, locktime;

//     txid = Data_Parser(0, 73, coinbase_data); // PROVIDED !LENGTH : 74 BYTES
//     vout = Data_Parser(74, 81, coinbase_data); // PROVIDED !LENGTH : 8 BYTES
//     sequence = Data_Parser(84, 91, coinbase_data); // PROVIDED !LENGTH : 8 BYTES
//     outputCount = Data_Parser(92, 93, coinbase_data);  // PROVIDED !LENGTH : 2 BYTES
//     Hexadecimal_blockReward = Data_Parser(94, 94+16-1, coinbase_data); // PROVIDED !!! -LENGTH : 16 BYTES
//     scriptPubKey = Data_Parser(94+16, locktime_denominate-1, coinbase_data); // PROVIDED !LENGTH : DYNAMIC SIZE OF BYTES
//     // locktime = Return_As_Given(Data_Parser(locktime_denominate, Data_Size-1, coinbase_data)); // PROVIDED !LENGTH : 8 BYTES
//     locktime = "00000000";// DEFINE LOCKTIME VALUE
//     vout = "ffffffff"; // from "ffffff7f" to "ffffffff"
//     Byte_PUSH = "03";// SET PUSH HEX 
//     LittleEndian_blockHeight = blockHEIGHT;// GENERATE LITTLE ENDIAN FORMATTED BLOCK HEIGHT
//     ArbitraryData = X_Data; // Get arbitrary data
//     tempInt = Byte_PUSH.length() + LittleEndian_blockHeight.length() + ArbitraryData.length();// CALCULATE SCRIPTSIG SIZE
//     scriptsig_Size = i_ConvertIntToHex(tempInt); // convert length of all data to hex format 
//     // CONCATENATE PARSED DATA
//     coinbase_data = txid + vout + scriptsig_Size + Byte_PUSH + LittleEndian_blockHeight + ArbitraryData + sequence + outputCount +  Hexadecimal_blockReward + scriptPubKey + locktime;

//     return coinbase_data;// RETURN COINBASE
// }// Successfully compiled on 31/01/2022 at 06:16AM



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	LOGGING AND TIME 
/////////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t PRE_randNum()
{
	uint32_t n =((uint32_t)rand()/(RAND_MAX)+1) +(rand()%57974); // generate a number for the sake of altering time
	return n;
}

uint32_t randNum(uint32_t k)	// requires a value to determine maximum number generatable
{ // uint32_t k determines the maximum value to be generated
	srand(time(0)+(PRE_randNum()-PRE_randNum()));  // Initialize random number generator.
	uint32_t n =((uint32_t)rand()/(RAND_MAX)+1) +(rand()%k); // generate a number from 1 to 10
	return n;
} // USAGE : randNum(5);...... uint32_t value = randNum(66);

void DYNAMIC_CreateLogFile(string height, string blockheader, string winningHash, string blockReward)
{
	string create_filename = "Block " + height + "WAS MINED" + ".txt";// Create file Name
	time_t ttime = time(0);
    char *dt = ctime(&ttime);
	
	ofstream MyFile(create_filename); 	// Create or open a text file
	MyFile << "Congratulations Mr Grada, you successfully mined block " << height << ".\nBLOCK DETAILS :\n\nBlock header : " << blockheader  << "\n \nNumber of transactions : 1(COINBASE TRANSACTION)\n \nWinning Hash is : " << winningHash << "\n \nReward fee : " << blockReward;
	MyFile << "\n \n \nCONGRATULATIONS....... YOU BEAT THE ODDS!! GOD'S GIFT IS REAL! DON'T FORGET TO PRAISE HIM ";
	MyFile << "\n \n \n \n \nDate and time is   :  " << dt;
	MyFile.close(); 	// Close the file
}

inline void SubmitFile(string encodedhexdata, string destination)
{
    ofstream MyFile(destination);// Create or open a text file
    MyFile << encodedhexdata;// Write to the file
    MyFile.close(); // Close the file
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	EXTRA
/////////////////////////////////////////////////////////////////////////////////////////////////////////


uint32_t StringTo_32Uint(string x)
{
    uint32_t z = 0;
    stringstream xx;
    xx << x;
    xx >> z;
    xx.clear();
    return z;
}// Successfully compiled on 27/01/2022 at 11:23PM


void RunCommand_With_Output_Without_SYMBOL_Defined(string Command_To_Run, string Output_FileName)
{
    string xx_combine = Command_To_Run + " >" + Output_FileName;
    char run_command[xx_combine.length()];
    strcpy(run_command, xx_combine.c_str());
    system(run_command); // execute the command // std::cout << std::ifstream(Output_FileName).rdbuf(); // print to console -- FOR DEBUGGING ONLY!!
} // Successfuly compiled on 20/01/2022 10:20PM



void RunCommand(string Command_To_Run)
{
    char run_command[Command_To_Run.length()];
    strcpy(run_command, Command_To_Run.c_str());
    system(run_command); // execute the command 
}



#endif