import random
import string
from typing import Dict

from src.exceptions import ParseError
from src.text_encryption.encrypted_text import EncryptedText


class CharReplaceEncryption(EncryptedText):
    def __init__(self):
        super().__init__()
        self._encrypted_text: str | None = None
        self._replace_pairs: Dict[chr, chr] | None = None

    def __repr__(self):
        return f"[Char replace encryption:\n" \
               f"\tencrypted_text: {self._encrypted_text}\n" \
               f"\tdecrypted_text: {self._decrypted_text}\n" \
               f"\tsum_div_length: {self.sum_div_length}]"

    def random_fill(self):
        str_len = random.randint(1, 100)

        chars = string.digits + string.ascii_letters + " "

        self._encrypted_text = ''.join(random.choice(chars) for _ in range(str_len))
        self._replace_pairs = {char: random.choice(chars) for char in self._encrypted_text}

        self.decrypt()
        return self

    def decrypt(self):
        self._decrypted_text = ''
        for char in self._encrypted_text:
            val = self._replace_pairs.get(char)
            self._decrypted_text += val if val is not None else char

    def fill_from_str(self, input_str: str):
        try:
            pairs_count, input_str = input_str.split(' ', 1)
            pairs_count = int(pairs_count)
            self._replace_pairs = dict(zip(input_str[pairs_count:pairs_count * 2], input_str[:pairs_count]))
            self._encrypted_text = input_str[pairs_count * 2 + 1:]
        except Exception:
            raise ParseError("CharReplaceEncryption parse error")
        self.decrypt()
        return self
