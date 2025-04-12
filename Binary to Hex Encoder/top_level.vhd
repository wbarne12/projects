-- Stanley Barnes
-- wbarne12@vols.utk.edu
-- 000657926
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity top_module is
    port (
        clk_in : in std_logic;        
        Key    : in std_logic;        -- button
        fA, fB, fC, fD, fE, fF, fG : out std_logic
    );
end top_module;

architecture Behavioral of top_module is

    -- Component declarations
    component db_pulse is
        port (
            Clk1  : in std_logic;  
            Key   : in std_logic;  
            pulse : out std_logic  
        );
    end component;

    component d_ff is
        port (
            d_in  : in std_logic;  
            clock : in std_logic; 
            q_out : out std_logic 
        );
    end component;

    component bin_to_hex is
        port (
            A, B, C, D : in std_logic; 
            fA, fB, fC, fD, fE, fF, fG : out std_logic  
        );
    end component;

    signal db_pulse_out : std_logic;        
    signal q : std_logic_vector(3 downto 0); 
    signal d : std_logic_vector(3 downto 0); 

begin

    -- Getting the clock
    debounce_inst: db_pulse
        port map (
            Clk1  => clk_in,
            Key   => Key,
            pulse => db_pulse_out
        );

    -- Counter logic
    -- Lab write up said 3 bit counter and 4 bit, so I did 4 bit
    d(0) <= not q(0);                    
    d(1) <= q(0) xor q(1);              
    d(2) <= (q(1) and q(0)) xor q(2);  
    d(3) <= (q(2) and q(1) and q(0)) xor q(3); 

    dff_0: d_ff
        port map (
            d_in  => d(0),
            clock => db_pulse_out,
            q_out => q(0)
        );

    dff_1: d_ff
        port map (
            d_in  => d(1),
            clock => db_pulse_out,
            q_out => q(1)
        );

    dff_2: d_ff
        port map (
            d_in  => d(2),
            clock => db_pulse_out,
            q_out => q(2)
        );

    dff_3: d_ff
        port map (
            d_in  => d(3),
            clock => db_pulse_out,
            q_out => q(3)
        );

    bin_to_hex_inst: bin_to_hex
        port map (
        -- In the decoder, D is the most significant bit while A is the least
            A => q(3),
            B => q(2),
            C => q(1),
            D => q(0),
            fA => fA,
            fB => fB,
            fC => fC,
            fD => fD,
            fE => fE,
            fF => fF,
            fG => fG
        );

end Behavioral;