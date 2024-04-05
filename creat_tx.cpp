#include "include/bin_con.h"
#include "include/ripemd160.h"
#include "include/g_sha256.h"



// BigInteger a, z, p, n, b, G_X, G_Y, GXY, nVariant, pVariant, diff, pubX, pubY, pubXY, pk;
BigInteger p = stringToBigInteger("115792089237316195423570985008687907853269984665640564039457584007908834671663"); // module factor on curve point
BigInteger n = stringToBigInteger("115792089237316195423570985008687907852837564279074904382605163141518161494337"); // maximum value for privateKey
BigInteger b = stringToBigInteger("7"); // Who doesn't like the number 7 ? RONALDO.... RONALDO..... RONALDO.....
BigInteger G_X = stringToBigInteger("55066263022277343669578718895168534326250603453777594175500187360389116729240"); // G point x value
BigInteger G_Y = stringToBigInteger("32670510020758816978083085130507043184471273380659243275938904335757337482424"); // G point y value
BigInteger GXY = stringToBigInteger("5506626302227734366957871889516853432625060345377759417550018736038911672924032670510020758816978083085130507043184471273380659243275938904335757337482424");
BigInteger nVariant = String_2_BigInteger("2198991635514169179907010015771618769820070228769668761459910881962896343235"); // n variant
BigInteger pVariant = String_2_BigInteger("2198991635514169179907010015771618770252490615335328418312331748353569520561"); // p variant
BigInteger diff = p-n; // difference between p and n ??????!!!!!



// PROTOTYPE

BigInteger randBigNum();
bool ISOWNER_VALID(vector<string> data, char scriptType, string SCRIPT_SIG, string SCRIPT_PUBLICKEY);
void Decipher_RawTx(string raw_txid);
string create_transaction(string SourceTxid, string vout, string publicKey, string privateKey, string amount, string recievingAddress, string ChangeAddress, string sequence, string locktime);// this function assumes to know the vout and amount by default
string LockScript(string InitialLS, string pubKey, string sig, string Amount);
vector<string> unlockScript(string LockingScript);
string Generate_Signature(string script_hash, BigInteger pk);
BigInteger modInverse(BigInteger m);
bool validate_Signature(string tx_signature, string generated_Signature);



//

string HASH160(string data)
{
	return ripemd160(sha256(data));
}


BigInteger privateKey(string pbk)
{

}

string sign_Transaction(BigInteger pk)
{

}



string CheckPublicKeyPool(string dt)
{

}



BigInteger randBigNum()
{
	uint32_t n =((uint32_t)rand()/(RAND_MAX)+1) +(rand()%987974); // generate a number for the sake of altering time
	srand(time(0)+(n-n));  // Initialize random number generator.
	BigInteger drb =((uint32_t)rand()/(RAND_MAX)+1) +(rand()%9087646); // generate a number from 1 to 10
	BigInteger j = String_2_BigInteger("425364785907659487265435467589069548736526378765432345");
	string f, b;

	for (int i = 0; i < 32; ++i)
	{
		drb*=2;
		drb+= drb%94323; // j;
		f = BigInteger2String(drb);
		if (f.length() >= 78)
		{
			for (int g = 0; g < 77; g)
				b+=f;
			break;
		}
		else if(f.length() < 77 && i == 31)
			i = 0; // continue loop
	}
	drb = String_2_BigInteger(b);
	while(drb > n)
	{
		drb = drb%n+j;
	}

	return drb;
}


// for now only 2 script types are implemented
// P2PK [k] and P2PKH [h]
bool ISOWNER_VALID(vector<string> data, char scriptType, string SCRIPT_SIG, string SCRIPT_PUBLICKEY) 
{
	bool a, b;
	string check;
	if (scriptType == 'k') // This locking script was locked to a P2PK script
	{ // Check for matching signature derived from correlating privateKey
		check = HASH160(data[2]+data[2]); // duplicate and hash using sha256 and then ripemd160
		if(check == SCRIPT_PUBLICKEY) // ??????????????????
		{
			a = true; // set a to true, hash output matches locking script data
			if(data[0] == SCRIPT_SIG) // if signature generated is same as signature of locking script
				b = true; // User is true owner because only user with matching privateKey could create correlating signature
		}
	}
	else if (scriptType == 'h') // This locking script was locked to a P2PKH script
	{// Check for matching signature derived from correlating privateKey as well as hash checksum??????????????????????
		check = HASH160(data[2]+data[2]); // duplicate and hash using sha256 and then ripemd160
		if(check == SCRIPT_PUBLICKEY) // ??????????????????
		{
			a = true; // set a to true, hash output matches locking script data
			if(data[0] == SCRIPT_SIG) // if signature generated is same as signature of locking script
				b = true; // User is true owner because only user with matching privateKey could create correlating signature
		}
	}

	if(a == true && b == true)
		return true;

	return false;
}




void Decipher_RawTx(string raw_txid)
{
	// first 8 bytes are version

	// after that next 2 bytes are input count in hexadecimal. This value tells you how many upcoming characters belong to the unlocking script

	// after which 
}


string create_transaction(string SourceTxid, string vout, string publicKey, string privateKey, string amount, string recievingAddress, string ChangeAddress, string sequence, string locktime)// this function assumes to know the vout and amount by default
{// Amount can still be derived systematically
	//

	// if certain variables are set as 0, issue default value, otherwise insert given value
	// These variables include: sequence, locktime
}




string LockScript(string InitialLS, string pubKey, string sig, string Amount)
{
	string signature, signature_length, public_key, public_key_length;

	// signature = sign_Transaction(privateKey); // 
	// signature_length = IntegerToHex(signature.length()/2);
	// public_key = CheckPublicKeyPool(outputPublicKey);
	// public_key_length = IntegerToHex(public_key.length()/2);


	// sign_Transaction();

}

/*needed for extracting publicKey of intended recipient before function fetches said pbs pk for signature generation*/
// passes Entire lockingScript and derives publicKey or address hash for selection of correlating privateKey and accuracy of signature to be generated
vector<string> unlockScript(string LockingScript)
{
	vector<string> rkt, sx;
	char type;
	// Extract publicKey from script
	string TargetPublicKey, TargetSignature;
	TargetPublicKey = "";
	TargetSignature = "";

	string signature, signature_length, public_key, public_key_length;
	public_key = CheckPublicKeyPool(TargetPublicKey); // Go through list of publicKeys/publicKeyHashes and match that of locking script
	public_key_length = IntegerToHex(public_key.length()/2); // Get publicKey address hash length

	signature = sign_Transaction(privateKey(public_key)); // generate random number and use private key to generate signature
	signature_length = IntegerToHex(signature.length()/2); // get signature length
	
	// Basic data needed to unlock a UTXO for P2PKH and P2PK locking scripts
	rkt.push_back(signature); // index 0
	rkt.push_back(signature_length); // index 1
	rkt.push_back(public_key); // index 2
	rkt.push_back(public_key_length); // index 3

	if (ISOWNER_VALID(rkt, type, TargetSignature, TargetPublicKey) == true || validate_Signature(TargetSignature, rkt[0]) == true)
		cout << "Signature is correct, Bitcoin will be released to you.\n\n";
	else{cout << "I dont think signature is correct!\n\n";}

	return rkt;

	// PublicKey, Random seed Signature, default Opcode functions and checks
	// PublicKey, Random seed Signature : HASH160(), isMatch()- for publicKey check, validate_Signature() - for final sig check
}




string Generate_Signature(string script_hash, BigInteger pk)
{
	vector<string> pubK;
	string sig, RandomValue_X_Point; // Calculated publicKey of ranomly generated number 
	BigInteger sig_t, randomValue = randBigNum();
	// Generate_PublicKey(randomValue, pubK);
	RandomValue_X_Point = pubK[0];
	// sig = {
	// 	BigInteger z, d;
	// 	sig = ModularInverse(k) * (z + r * d);
	// 	return sig;
	// }







	if (sig_t > (n/2))
		sig_t = n - sig_t;

	sig = BigInteger2String(sig_t); // convert large decimal to hexadecimal string

	return sig;
}






BigInteger modInverse(BigInteger a, BigInteger m)
{
	BigInteger prevy, q, o_o, y; // DECLARE VARIABLES
	o_o = m; // create copy of initial starting point for later use 
	
	if(a<0) // if a is less than 0
		a = a % m, y = 0, prevy = 1;  // set y = 0 and prevy = 1  
	
	while(a>1) // while a is greater than 1
	{
		q = m / a; // Divide m by a and store result in q
		prevy = prevy - (q * y); // subtract prevy from the result of q * y
		m = m % a; // mod m by a
	}
	y = y % o_o; // mod y by original initial starting point
	// if function was set to return a value
	return y;
} // 03:35PM 15/09/2022 FINISHED CREATION





BigInteger Inverse(BigInteger a, BigInteger m)
{
	BigInteger prevy(0), y(1), q, m_orig = m, der(0);
	// m = p;
	if (a < 0)
		a = a % m;

	while(a > 1) 
	{
	    q = m/a;
	    y = (prevy-q)*y;
	    prevy = y;
	    a = m % a;
	    m = a;
	}
	der = y % m_orig;
	return der;
}




bool validate_Signature(string tx_signature, string generated_Signature)
{
	if(tx_signature == generated_Signature)
		return true;
	return false;
}

/*

	random number    (k): 123456789
	hash256(message) (z): 75402077471587956851360588120356244127735644006942973877340910814730793844683
	private key      (d): 112757557418114203588093402336452206775565751179231977388358956335153294300646

	random point (k*G = R): {
	  x = 4051293998585674784991639592782214972820158391371785981004352359465450369227,
	  y = 88166831356626186178414913298033275054086243781277878360288998796587140930350
	}

	signature: r = R[x], s = k⁻¹ * (z + r * d): {
	  r = 4051293998585674784991639592782214972820158391371785981004352359465450369227, 
	  s = 101656099268479774907861155236876278987061611115278341531512875302287938750185
	}
*/



int main(int argc, char const *argv[])
{
	// collect scriptsig data from 
	// dispense data into pairs
	// correct paired data
	// reassemble data
	// add extra bits according to transaction type and mainnet protocol
	// concatenate everything together
	// feed data back into raw transaction string

	BigInteger z, pk, k, s, r, v;
	z = String_2_BigInteger("75402077471587956851360588120356244127735644006942973877340910814730793844683");
	pk = String_2_BigInteger("112757557418114203588093402336452206775565751179231977388358956335153294300646");
	k = String_2_BigInteger("123456789");
	r = String_2_BigInteger("4051293998585674784991639592782214972820158391371785981004352359465450369227");
	// s = (z + r * pk);
	// cout << "s = " << s << "\n";
	// v = Inverse(k, p);
	// cout << "v = " << v << "\n";
	// s = v * s;

	s = Inverse(k, p) * (z + r * pk);


	cout << "signature y point = " << s%p+p << "\n\n";


	return 0;
}












// pb = k*G;
// k = (pb/G)*pb; or k = pb/G*G; or k = pb/G%p; or k = pb/G%n; or k = pb/G%G; or k = pb/G%pb;
// k = pb%G; or k = pb/G%G;
// if n = G, set n = 0? opposite of infinity point, call it implosion Point 15/11/22 07:17 AM



/*

asm: [signature length] [signature] [public key length] [public key]
hex: 473044022008f4f37e2d8f74e18c1b8fde2374d5f28402fb8ab7fd1cc5b786aa40851a70cb02201f40afd1627798ee8529095ca4b205498032315240ac322c9d8ff0f205a93a580121024aeaf55040fa16de37303d13ca1dde85f4ca9baa36e2963a27a1c0c1165fe2b1


Unlock a p2pkh output

47 - signature length
3044022008f4f37e2d8f74e18c1b8fde2374d5f28402fb8ab7fd1cc5b786aa40851a70cb02201f40afd1627798ee8529095ca4b205498032315240ac322c9d8ff0f205a93a5801 - signature
21 - public key length
024aeaf55040fa16de37303d13ca1dde85f4ca9baa36e2963a27a1c0c1165fe2b1 - public key

*/










