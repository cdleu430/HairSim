<<<<<<< HEAD
# Leu Hair Simulation

This is a simple hair simulation, done using mass-springs and RK4 integration.

Things you can change that the UI doesn't include:
  Amount follow hairs are spread out from the guides:
    In NGLScene.cpp -> initialGL, change the HI and LO variables in the create hair section, they should be 2 values that are slightly more or less than 1

  Simpler collisions with scalp:
    In GuideHair.cpp -> updateJoints, change complexCollision to simpleCollision

  How far off the scalp hairs rest:
    In GuideHair.cpp -> updateJoints scalp penetration section, change .05 to something else
=======
# ase-cgitech201718-cdleu430
>>>>>>> 77d5517397eb2c5e9ae965dccfce49eeaf0cfb81
