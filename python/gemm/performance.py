
def FC_time(freq, word_size, cols, lhs_rows, rhs_rows,
    lhs_bits, rhs_bits, chn):

  """
    Time per FC layer execution
    Does not account for time taken by reading and writing to DRAM,
    which i'm not sure about
  """
  cycles_per_dot_prod = 4
  cycles_per_dynamic_read_prep = 5
  cycles_between_row_pairs = 1

  cycles_per_row_pair = cycles_per_dot_prod * (cols/word_size) \
    + cycles_per_dynamic_read_prep + cycles_between_row_pairs

  cycles_per_channel = cycles_per_row_pair * lhs_rows * rhs_rows \
    * lhs_bits * rhs_bits * chn

  t = freq * cycles_per_channel
  return t

f = 1/(50*10**6) # 50MHz
a = FC_time(freq=f, word_size=64, cols=1024, lhs_rows=256, rhs_rows=1,
  lhs_bits=1, rhs_bits=1, chn=3)
print("bit_depths=(1,1) -> ", a)

a = FC_time(freq=f, word_size=64, cols=1024, lhs_rows=256, rhs_rows=1,
  lhs_bits=2, rhs_bits=2, chn=3)
print("bit_depths=(2,2) -> ", a)




