# Constant-Potential-SEI-SIBs

This repository contains the relevant simulation input files used for
the NaFSI/DME electrolyte system with a metallic sodium electrode. The
force-field folder contains the corresponding molecular topology, atomic
charge, and force-field parameter information used in these simulations.

Paper Link: 


# NaFSI/DME--Na Electrode Simulation Force Field

## Atomic Charges and Molecular Topology

The atomic charges assigned to the electrolyte species can be found in
the corresponding `.itp` files.

The `.itp` files also contain the molecular topology information,
including:

-   Atomic charges
-   Bond definitions
-   Angle definitions
-   Dihedral definitions

## OPLS-AA Force-Field Parameters

The OPLS-AA force-field parameters used in the simulations can be
identified from the corresponding LAMMPS data/input files. The
force-field type assignments are organized as follows.

### Pair Coefficients / Atom Types

  Type ID   Species
  --------- --------------------------------------------
  1         Na⁺ ion
  2--5      FSI⁻
  6--21     DME
  22        Metallic Na electrode, \[110\] orientation

### Bond Coefficients

  Bond Type   Species
  ----------- ---------
  1--3        FSI⁻
  4--18       DME

### Angle Coefficients

  Angle Type   Species
  ------------ ---------
  1--5         FSI⁻
  6--31        DME

### Dihedral Coefficients

  Dihedral Type   Species
  --------------- ---------
  1--2            FSI⁻
  3--23           DME

## Notes

> **To be updated:** Additional information regarding force-field
> parameterization, simulation setup, file organization, parameter
> sources, validation, and usage instructions will be added here.

## Citation

> **To be added:** Relevant publication(s) and force-field references
> will be provided here.
