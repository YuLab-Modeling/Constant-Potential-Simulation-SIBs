units real
boundary p p f # slab calculation

atom_style full
pair_style lj/cut/coul/long 10
bond_style harmonic
angle_style harmonic
dihedral_style opls
kspace_style pppm/electrode 1e-4
kspace_modify slab 3.0
special_bonds lj/coul 0.0 0.0 0.5 

read_data "nafsi_dme_na501.data"     # This is my Data file 

group ele type 22
group sol type 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
group fsi type 2 3 4 5 
group fsi_catom type 3
group fsi_catom2 type 2
group dme_catom type 7 10
group ion type 1
group dme type 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
group left molecule  1952   #Change it according to the structure
group right molecule 1953  #Change it according to the strucuture
group rdf_all type 1 2 7 10


neighbor 10 bin
neigh_modify	one 10000 delay 0 every 1 check yes

# Fixed Electrode - velocity zero - must come before minimization
velocity ele set 0.0 0.0 0.0
fix 0 ele setforce 0.0 0.0 0.0

timestep 2

min_style   cg
minimize 1.0e-6 1.0e-6 10000 10000
reset_timestep 0


fix shake0 dme shake 0.0001 20 10000000 b 9 10 11 12 13 14 15 16 17 18
fix nvt sol nvt temp 350.0 350.0 100

variable q atom q
compute qleft left reduce sum v_q
compute qright right reduce sum v_q
compute ctemp sol temp


fix conp right electrode/conp 2 1.979 couple left -2 symm on


# Dumping Files

dump 1 ele custom 500 ele id q
dump_modify 1 sort id

# These all dump_xyz data can also be extracted from all.xyz file using MATLAB
dump 3 ion xyz 500 na_ion.xyz
dump 4 fsi_catom xyz 500 fsi_N.xyz
dump 5 fsi_catom2 xyz 500 fsi_O.xyz
dump 6 dme_catom xyz 500 dme_O.xyz

dump 7 all xyz 500 all.xyz
dump 8 all dcd 500 all.dcd

dump            13 all custom 500 all.lammpstrj id type x y z vx vy vz
dump_modify     13 sort id


# Define the number of divisions in the z-direction
variable num_bins equal 400
variable z_min equal 0
variable z_max equal 80
variable bin_width equal (${z_max}-${z_min})/${num_bins}

# Create a compute to count atoms in bins along z
compute binning_na ion chunk/atom bin/1d z lower ${bin_width} units box
compute binning_fsi fsi_catom chunk/atom bin/1d z lower ${bin_width} units box
compute binning_fsi2 fsi_catom2 chunk/atom bin/1d z lower ${bin_width} units box
compute binning_dme dme_catom chunk/atom bin/1d z lower ${bin_width} units box

# Dump the averaged atom density into a .txt file
fix count_bins_ion ion ave/chunk 100 100 10000 binning_na density/number file atom_density_ion.txt
fix count_bins_fsi fsi_catom ave/chunk 100 100 10000 binning_fsi density/number file atom_density_fsi_N.txt
fix count_bins_fsi2 fsi_catom2 ave/chunk 100 100 10000 binning_fsi2 density/number file atom_density_fsi_O.txt
fix count_bins_dme dme_catom ave/chunk 100 100 10000 binning_dme density/number file atom_density_dme.txt


## Compute average charge and dumping 
compute ch_c ele property/atom q
fix ch_f ele ave/atom 10 50 500 c_ch_c
dump ch_d ele custom 500 charge_average id f_ch_f
dump_modify ch_d sort id

compute myRDF rdf_all rdf 500 1 2 1 7 1 10
fix rdf1 rdf_all ave/time 10 50 500 c_myRDF[*] file rdf_all.txt mode vector

thermo 50000
thermo_style custom step temp c_ctemp epair etotal c_qright c_qleft
restart 1000000 restart
run 10000000


