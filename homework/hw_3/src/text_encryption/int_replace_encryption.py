import random
import string
from typing import List, Dict

from src.exceptions import ParseError
from src.text_encryption.encrypted_text import EncryptedText


class IntReplaceEncryption(EncryptedText):
    def __init__(self):
        super().__init__()
        self._encrypted_text: List[int] | None = None
        self._replace_pairs: Dict[int, chr] | None = None

    def __repr__(self):
        return f"[Int replace encryption:\n" \
               f"\tencrypted_text: {self._encrypted_text}\n" \
               f"\tdecrypted_text: {self._decrypted_text}\n" \
               f"\tsum_div_length: {self.sum_div_length}"

    def random_fill(self):
        str_len = random.randint(1, 100)

        chars = string.digits + string.ascii_letters + " "

        self._encrypted_text = [random.randint(0, 10000) for _ in range(str_len)]
        self._replace_pairs = {i: random.choice(chars) for i in self._encrypted_text}

        self.decrypt()
        return self

    def decrypt(self):
        self._decrypted_text = "".join([self._replace_pairs[i] for i in self._encrypted_text])

    def fill_from_str(self, input_str: str):
        try:
            pairs_count, input_str = input_str.split(' ', 1)
            pairs_count = int(pairs_count)
            ints = list(map(int, input_str[pairs_count + 1:].split()))
            self._replace_pairs = dict(zip(ints[:pairs_count], input_str[:pairs_count]))
            self._encrypted_text = ints[pairs_count:]
        except Exception:
            raise ParseError("IntReplaceEncryption parse error")
        self.decrypt()
        return self
