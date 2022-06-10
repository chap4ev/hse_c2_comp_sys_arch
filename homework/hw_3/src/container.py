import random
import re
from collections.abc import Sequence
from pathlib import Path
from typing import List

from src.text_encryption.encrypted_text import EncryptedText
from src.text_encryption.int_replace_encryption import IntReplaceEncryption
from src.text_encryption.char_replace_encryption import CharReplaceEncryption
from src.text_encryption.cycle_encryption import CycleEncryption


class Container(Sequence):
    def __init__(self):
        self.data: List[EncryptedText] = []

    def __len__(self):
        return len(self.data)

    def __getitem__(self, item):
        return self.data[item]

    def fill_randomly(self, count: int):
        for _ in range(count):
            encryption_type = random.choice([IntReplaceEncryption, CharReplaceEncryption, CycleEncryption])
            self.data.append(encryption_type().random_fill())

    def fill_from_file(self, file_path: str):
        input_file_text = Path(file_path).read_text()
        re_pattern = "CycleEncryption|IntReplaceEncryption|CharReplaceEncryption"
        all_matches = list(re.finditer(re_pattern, input_file_text))
        all_matches_entries = []
        for i in range(0, len(all_matches) - 1):
            all_matches_entries.append(
                (all_matches[i].group(), all_matches[i].end() + 1, all_matches[i + 1].start() - 1)
            )
        all_matches_entries.append((all_matches[-1].group(), all_matches[-1].end() + 1, len(input_file_text)))

        for match, start_pos, end_pos in all_matches_entries:
            if match == "CycleEncryption":
                self.data.append(CycleEncryption().fill_from_str(input_file_text[start_pos: end_pos]))
            elif match == "IntReplaceEncryption":
                self.data.append(IntReplaceEncryption().fill_from_str(input_file_text[start_pos: end_pos]))
            elif match == "CharReplaceEncryption":
                self.data.append(CharReplaceEncryption().fill_from_str(input_file_text[start_pos: end_pos]))

    def sort(self):
        """Сортировка по возрастанию с помощью прямого выбора (Straight Selection)"""
        for i in range(0, len(self.data)):
            min_i = i
            for j in range(i + 1, len(self.data)):
                if self.data[j].sum_div_length < self.data[min_i].sum_div_length:
                    min_i = j
            self.data[i], self.data[min_i] = self.data[min_i], self.data[i]
