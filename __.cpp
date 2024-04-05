// Copyright© 2021, 2022 David GradaSupreme. This code belongs to Mr David GradaSupreme

#include "__.h"

string GLOBAL_COINBASEVALUE;

// // Make sure to confirm if endianness of this function matches endianness of nTime,
// // nBits & nNonce from the main body as wrong mixture of endianness will be COSTLY!!!!
bool BlockCheck(string hash, string header, string raw_coinbase, string target)
{
	hash = SwapPerRound_2bits(hash);
	// string target = Get_HASH_TARGET();
	BigInteger z = HexToInteger(hash), k = HexToInteger(target);
	if ((z == k) || (z < k) || (((k - z) == 1) && ((k-z) < 5)))
	{
		string a = Get_BLOCK_HEIGHT_asString(), e = Transform_String_To_Double();
		string EncodedHexData = header + No_Of_Txs() + raw_coinbase + AppendAllRawTransactions();
		// Sleep(1000); // pause program fro 3 seconds and give system enough time to fill variable with all aw tx stringd which are extremely large

		if ((z == k) || (z < k)) // ihash is equal or lesser than target
		{
			string SubmitBlock = "cd \"C:\\Users\\Ancient Tides\\Desktop\\__\" && call submit_blockhash.bat";
			SubmitFile(EncodedHexData, "BlockCandidate_1.txt");
	    	DYNAMIC_CreateLogFile(a, header, hash, e);
	    	Sleep(1000);
	    	RunCommand(SubmitBlock);
	    	cout << "Candidate hash for submission is | " << hash << "\n\n";
		}
		else if (((k - z) == 1) || (k-z < 10))
		{
			SubmitFile(EncodedHexData, "BlockCandidate_1.txt");
			string SubmitBlock = "cd \"C:\\Users\\Ancient Tides\\Desktop\\__\" && call submit_blockhash.bat";
	    	DYNAMIC_CreateLogFile(a, header, hash, e);
	    	Sleep(1000);
	    	RunCommand(SubmitBlock);
	    	cout << "Candidate hash for submission is | " << hash << "\n\n";
		}
		return true;
	}
	else
		return false;		
}



int main(int argc, char const *argv[])
{
// Beginning: // Entry point for restarting hash generation
	GETBLOCKTEMPLATE();
	string HashData, RETURNDATA;
	string nVersion, prevHash, merkleHash, nBits, string_nNonce, string_nTime, raw_coinbase_tx, nTarget, blockHEIGHT;
    string coinbase_data = ScriptSigParser(createRawTx(), Get_BLOCK_HEIGHT_asString(), Pad_HexString(IntegerToHex(randNum(4294967294))));
    raw_coinbase_tx = COINBASETX_TX(createRawTx(), Get_BLOCK_HEIGHT_asString(), Pad_HexString(IntegerToHex(randNum(4294967294))));
    blockHEIGHT = Get_BLOCK_HEIGHT_asString();
    merkleHash = MKccx(coinbase_data, Get_TransactionVector());// create merkleroot
    nTarget = Get_HASH_TARGET();
    nVersion = SwapPerRound_2bits(IntegerToHex(Get_Numeric_Version()));
	prevHash = SwapPerRound_2bits(Get_PREVIOUS_BLOCK_HASH());
	nBits = SwapPerRound_2bits(Get_CURRENT_BLOCK_BITS());

	int nTime_Tracker = 0;// Initialize nTime_Tracker as int. Tracks nTime value
	uint32_t timestamp = time(0);/* Keeps current time before hashing algorithm begins */, dynamic = timestamp, nTime, nNonce, hashesDone, nonce_numeric_tracker;
	nTime = Get_Numeric_MINTIME();
	nNonce = 0;// Initialize nNonce as hexadecimal with 8 bit padding
	nonce_numeric_tracker = 0;
	hashesDone = 0; // Hash Tracker
	

	while (true)
	{
		string_nTime = SwapPerRound_2bits(IntegerToHex(nTime)); // convert ntime to string
		string_nNonce = SwapPerRound_2bits(Pad_AlphaSIZE_INT3HEX(nNonce)); // convert nNonce to hex string
		RETURNDATA = nVersion + prevHash + merkleHash + string_nTime + nBits + string_nNonce;
		HashData = double_Hex_sha256(RETURNDATA); // Double hash Data
		// std::cout << "Block header is >| " << RETURNDATA << "|<\n\n";
		hashesDone++;

		if (BlockCheck(HashData, RETURNDATA, raw_coinbase_tx, nTarget); == true)
			cout << "Candidate hash for submission is | " << HashData << "\n\n";

		nonce_numeric_tracker++;
		nNonce = nonce_numeric_tracker;
		nTime++;
		if (nonce_numeric_tracker == 4294967295)
		{
			nonce_numeric_tracker = 0;
			nTime++;
			nTime_Tracker++;
		}
		if ((time(0) - dynamic) == 180)
		{
			cout << "Generated hash is | " << SwapPerRound_2bits(HashData) << " | Hashes Generated "<< hashesDone<<"\n";
			dynamic = time(0);
			GETBLOCKTEMPLATE();
			string newBlockHeight = Get_BLOCK_HEIGHT_asString();
			if(newBlockHeight != blockHEIGHT)
			{// generate random number, convert to hexadecimal
				string coinbase_data = ScriptSigParser(createRawTx(), Get_BLOCK_HEIGHT_asString(), Pad_HexString(IntegerToHex(randNum(4294967294))));
    			raw_coinbase_tx = COINBASETX_TX(createRawTx(), Get_BLOCK_HEIGHT_asString(), Pad_HexString(IntegerToHex(randNum(4294967294))));
    			merkleHash = MKccx(coinbase_data, Get_TransactionVector());// create merkleroot
				nVersion = SwapPerRound_2bits(IntegerToHex(Get_Numeric_Version()));
				prevHash = SwapPerRound_2bits(Get_PREVIOUS_BLOCK_HASH());
				nBits = SwapPerRound_2bits(Get_CURRENT_BLOCK_BITS());
				nTime = Get_Numeric_MINTIME();
				blockHEIGHT = newBlockHeight; // update block height
			} // END OF NEW WORK CHECK STATEMENT
		} // END OF 3 MINUTES CHECK STATEMENT
	} // END OF WHILE LOOP
	// goto Beginning; // Then get newwork
	return 0;
}

