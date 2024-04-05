

// #include "include/bin_con.h"
// #include "include/g_sha256.h"
#include "__.h"


void Serialize_Transaction(/*vector<string> txIds*/);
void Serialize_Transaction(vector<string> txIds, vector<string> rawData, vector<string> txFees, string prevBk);



uint32_t globalTime = time(0);


string bits_To_TargetHash(string nbit)
{
	string th, temp, bxt;
	for(int k = 2; k < nbit.length(); k++)
		temp += nbit[k];
	bxt = nbit[0], bxt += nbit[1]; // get coefficient hex byte from first 2 hex chars 
	BigInteger xx = String_2_BigInteger(bxt); // convert hex BigInteger variable xx
	BigInteger _8(8), _3(3), pp, _2(2); // define BigInteger variables
	pp = Hex_To_BigNum(temp); // convert last 6 hex chars into decimal
	xx = xx - _3;
	xx = Hex_To_BigNum(_8) * Hex_To_BigNum(xx);
	xx = BigInteger_power(_2, xx);
	xx = pp * xx;
	th = IntegerToHex(xx);
	
	return th;
} // 06/11/22 08:09 AM


int main(int argc, char const *argv[])
{
	// string b = "1903a30c", hash;
	// hash = bitsToTargetHash(b);
	// cout << "Target hash = " << hash << "\n";
	Serialize_Transaction();

	vector<string> tx, raw_data_, fees;
	string previousblockhash = "00000000000000000000000adf85a9f6f388244a210f411bbccc3f2389e1e2e0";

	// Serialize_Transaction(tx, raw_data_, fees, previousblockhash);

	cout << "\n\n";

	return 0;
}




string Get_PREVIOUS_BLOCK_HASH(string file)
{
	string request;
	ifstream file_input(file);
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	request = object.at("previousblockhash");
	return request;
}


string Get_HASH_TARGET(string file)
{
	string request;
	ifstream file_input(file);
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	request = object.at("target");
	return request;
}

string Get_BLOCK_HEIGHT_asString____(string file)
{
	stringstream jj;
	string request;
	uint32_t f;
	ifstream file_input(file);
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	f = object.at("height");
	jj << f;
	jj >> request;
    jj.clear();
	return request;
}



string Get_CURRENT_BLOCK_BITS____(string file)
{
	string request;
	ifstream file_input(file);
	json object = json::parse(file_input); // Parse json data
	file_input.close(); // close streamer
	request = object.at("bits");
	return request;
}


string Get_CoinbaseValue____(string file)
{
    stringstream jj;
    string request;
    uint32_t f;
    ifstream file_input(file);
    json object = json::parse(file_input); // Parse json data
    file_input.close(); // close streamer
    f = object.at("coinbasevalue");
    jj << f;jj >> request;jj.clear();
    return request;
}




void Serialize_Transaction(vector<string> txIds, vector<string> rawData, vector<string> txFees, string prevBk)
{
	string fn = "gbr.json";
	string p1, p2, txFormat, fee_temp, all, coinbase_value, targetHash, nbits, blockHeight, txid;
	nbits = Get_CURRENT_BLOCK_BITS____(fn);
	uint32_t currentTime = globalTime, calculated_mintime = currentTime-120;
	blockHeight = int2String(stringToDecimal(Get_BLOCK_HEIGHT_asString____(fn))+1);
	targetHash = bits_To_TargetHash(nbits); // SwapPerRound_2bits(bits_To_TargetHash(nbits));
	coinbase_value = Get_CoinbaseValue____(fn);

	p1 = "{\n\t\"version\": 536870912,\n\t\"previousblockhash\": \"" + prevBk + "\",\n\t\"transactions\": [\n";
	// for(int g = 0; g < txIds.size(); g++)
	// {
	// 	txFormat += "\t{\n\t\t\"data\": \"" + rawData[g] + "\",\n\t\t\"txid\": \"" + txIds[g] + "\",\n\t\t\"hash\": \"" + sha256(rawData[g]) + "\",\n\t\t" + "\"fee\": " + txFees[g] + ",\n\t}";
	// }
	
	txFormat = "\t\t{\n\t\t\"data\": \"" + all + "\",\n\t\t\"txid\": \"" + all + "\",\n\t\t\"hash\": \"" + all + "\",\n\t\t";
	fee_temp = "\"fee\": " + all + "\n\t\t}";
	p2 = "\n\t],\n\t\"coinbasevalue\": " + coinbase_value + ",\n\t\"target\": \"" + targetHash + "\",\n\t\"mintime\": " + int2String(calculated_mintime) + ",\n\t\"curtime\": " + int2String(currentTime) + ",\n\t\"bits\": \"" + nbits + "\",\n\t\"height\": " + blockHeight + "\n}";

	all = p1+txFormat+fee_temp+p2;
	// all = p1+txFormat+p2;

	cout << all << "\n";
}



void Serialize_Transaction()
{
	string fn = "gbr.json", p1, p2, txFormat, fee_temp, all, coinbase_value, targetHash, nbits, prevBk, blockHeight, txid;
	nbits = Get_CURRENT_BLOCK_BITS____(fn);
	uint32_t currentTime = globalTime, calculated_mintime = currentTime-120;
	blockHeight = int2String(stringToDecimal(Get_BLOCK_HEIGHT_asString____(fn))+1);
	targetHash = bits_To_TargetHash(nbits); // SwapPerRound_2bits(bits_To_TargetHash(nbits));
	coinbase_value = Get_CoinbaseValue____(fn);

	p1 = "{\n\t\"version\": 536870912,\n\t\"previousblockhash\": \"" + prevBk + "\",\n\t\"transactions\": [\n";
	txFormat = "\t\t{\n\t\t\"data\": \"" + all + "\",\n\t\t\"txid\": \"" + all + "\",\n\t\t\"hash\": \"" + all + "\",\n\t\t";
	fee_temp = "\"fee\": " + all + "\n\t\t}";
	p2 = "\n\t],\n\t\"coinbasevalue\": " + coinbase_value + ",\n\t\"target\": \"" + targetHash + "\",\n\t\"mintime\": " + int2String(calculated_mintime) + ",\n\t\"curtime\": " + int2String(currentTime) + ",\n\t\"bits\": \"" + nbits + "\",\n\t\"height\": " + blockHeight + "\n}";
	
	all = p1 + txFormat + fee_temp + p2;

	cout << all << "\n";
}
















































/*

{
  "version": 536870912,
  "previousblockhash": "000000000000000000069c3f6fa5f167e7359b28735089c8ffb5a46d8ddfa667",
  "transactions": [
    {
      "data": "",
      "txid": "a26ed093c4da4fe4efe914fdb7620e208c99e97512524dce9ca1fa60420358f2",
      "hash": "fa5035a97285049c14049bded40aabe8aa36d5e72f2a8651b4e274fa9e569f1a",
      "fee": 67000,
    }
  ],
  "coinbasevalue": 628987391,
  "target": "0000000000000000000a90800000000000000000000000000000000000000000",
  "mintime": 1643622069,
  "curtime": 1643625421,
  "bits": "170a9080",
  "height": 721176,
}

*/
















