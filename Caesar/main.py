#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
 
 
class CaesarEncrypt
{
	std::size_t shift_amount_;
 
public:
	explicit constexpr CaesarEncrypt(std::size_t shift_amount = {})
		: shift_amount_(shift_amount)
	{
		if (shift_amount >= alphabet_size)
		{
			throw std::invalid_argument("shift amount may not be greater than or equal to alphabet size");
		}
	}
 
	char shift_letter(char letter, bool back = false) const noexcept
	{
		std::size_t idx = letter;
 
		if (std::isupper(letter))
		{
			idx -= first_uppercase_letter;
		}
		else
			if (std::islower(letter))
			{
				idx -= first_lowercase_letter;
			}
			else
			{
				return letter;
			}
 
		return letter - idx + ((alphabet_size + (back ? idx - shift_amount_ : idx + shift_amount_)) % alphabet_size);
	}
 
	std::string encrypt_or_decrypt(std::string_view s, bool decrypt) const
	{
		std::string encrypted;
		std::for_each(s.begin(), s.end(), [this, decrypt, &encrypted](char const& ch) { encrypted.push_back(shift_letter(ch, decrypt)); });
		return encrypted;
	}
 
	 std::string encrypt(std::string_view s) const
	{
		return encrypt_or_decrypt(s, false);
	}
 
	std::string decrypt(std::string_view s) const
	{
		return encrypt_or_decrypt(s, true);
	}
 
	static constexpr std::size_t alphabet_size = 26;
	static constexpr char first_lowercase_letter = 'a';
	static constexpr char first_uppercase_letter = 'A';
};
 
int main()
{
	CaesarEncrypt ce(8);
	char const* const str{ "Hello World!" };
	auto const encrypted  = ce.encrypt(str);
	std::cout << encrypted << "\n";
	auto const decrypted = ce.decrypt(encrypted);
	std::cout << decrypted << "\n";
}
