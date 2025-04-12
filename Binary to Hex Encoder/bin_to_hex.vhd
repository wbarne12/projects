-- Stanley Barnes
-- wbarne12@vols.utk.edu
-- 000657926
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity bin_to_hex is
    port (
        A, B, C, D : in std_logic; 
        fA, fB, fC, fD, fE, fF, fG : out std_logic);
end bin_to_hex;

architecture Behavioral of bin_to_hex is
begin
    -- A'B'C'D + A'BC'D' + ABC'D + AB'CD
    fA <= ((not A) and (not B) and (not C) and D) or
          ((not A) and B and (not C) and (not D)) or
          (A and B and (not C) and D) or
          (A and (not B) and C and D);

    -- A'BC'D + ABD' + ACD + BCD'
    fB <= ((not A) and B and (not C) and D) or
          (A and B and (not D)) or
          (A and C and D) or
          (B and C and (not D));
          
    -- ABC'D' + A'B'CD' + ABC
    fC <= (A and B and (not C) and (not D)) or
          ((not A) and (not B) and C and (not D)) or
          (A and B and C);

    -- A'BC'D' + A'B'C'D + BCD + AB'CD'
    fD <= ((not A) and B and (not C) and (not D)) or
          ((not A) and (not B) and (not C) and D) or
          (B and C and D) or
          (A and (not B) and C and (not D));
    
    -- A'BC' + B'C'D + A'D
    fE <= ((not A) and B and (not C)) or
          ((not B) and (not C) and D) or
          ((not A) and D);
          
    -- A'B'D + A'B'C + A'CD + ABC'D
    fF <= ((not A) and (not B) and D) or
          ((not A) and (not B) and C) or
          ((not A) and C and D) or
          (A and B and (not C) and D);
          
    -- A'B'C' + A'BCD + ABC'D'
    fG <= ((not A) and (not B) and (not C)) or
          ((not A) and B and C and D) or
          (A and B and (not C) and (not D));    

end Behavioral;