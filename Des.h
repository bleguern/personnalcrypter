#ifndef DES_H_
#define DES_H_


enum CipherDir {ENCRYPTION, DECRYPTION};

class DES
{
	class Base
	{
	public:
		void UncheckedSetKey(CipherDir direction, const unsigned char *userKey, unsigned int length = 8);
		void ProcessAndXorBlock(const unsigned char *inBlock, const unsigned char *xorBlock, unsigned char *outBlock) const;

		void RawProcessBlock(unsigned long &l, unsigned long &r) const;

	protected:
		static const unsigned long Spbox[8][64];
		//FixedSizeSecBlock<unsigned long, 32> k;
	};

	public:
	
	static bool CheckKeyParityBits(const unsigned char *key);
	
	static void CorrectKeyParityBits(unsigned char *key);
	
	typedef BlockCipherTemplate<ENCRYPTION, Base> Encryption;
	typedef BlockCipherTemplate<DECRYPTION, Base> Decryption;
};

typedef DES::Encryption DESEncryption;
typedef DES::Decryption DESDecryption;


#endif