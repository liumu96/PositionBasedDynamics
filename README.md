# PositionBasedDynamics

- Determine the position corrections for a distance constraint between two particles:

  $C(\mathbf{p}_0, \mathbf{p}_1) = \| \mathbf{p}_0 - \mathbf{p}_1\| - l_0 = 0$

- Determine the position corrections for a dihedral bending constraint
  For a pair of adjacent triangles $(\mathbf{p}_1, \mathbf{p}_3, \mathbf{p}_2)$ and $(\mathbf{p}_1, \mathbf{p}_2, \mathbf{p}_4)$ with the common edge $(\mathbf{p}_3, \mathbf{p}_4)$ a bilateral bending constraint is added by the constraint function:

  $C_{bend}(\mathbf{p}_1, \mathbf{p}_2,\mathbf{p}_3, \mathbf{p}_4) = \text{acos}\left( \frac{\mathbf{p}_{2,1} \times \mathbf{p}_{3,1}}{|\mathbf{p}_{2,1} \times \mathbf{p}_{3,1}|} \cdot \frac{\mathbf{p}_{2,1} \times \mathbf{p}_{4,1}}{|\mathbf{p}_{2,1} \times \mathbf{p}_{4,1}|}\right)-\varphi_0$
  and stiffness $k_{bend}$. The scalar $\varphi_0$ is the initial dihedral angle between the two triangles and $k_{bend}$ is a global user parameter defining the bending stiffness.

- Determine the position correction for a constraint that conserves the volume of single tetrahedron. Such a constraint has the form :

  $ C(\mathbf{p}_1, \mathbf{p}\_2, \mathbf{p}\_3, \mathbf{p}\_4) = \frac{1}{6} \left(\mathbf{p}_{2,1} \times \mathbf{p}_{3,1}\right) \cdot \mathbf{p}_{4,1} - V_0$

  where $\mathbf{p}_1$, $\mathbf{p}_2$, $\mathbf{p}_3$ and $\mathbf{p}_4$ are the four corners of the tetrahedron and $V_0$ is its rest volume.
