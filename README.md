# Arcane Gameboard Group Repot
In case this is your first time using a Git like this, welcome! This may seem a bit daunting at first, but you really only need to know the basics.

## The Basics:
1. [Checkouts](https://www.atlassian.com/git/tutorials/using-branches/git-checkout)
    - When you checkout a branch/build you receive a specific version of code. Essentially what version you'd like to be using. Any edits that you make will be saved to that specific branch as well, so it's best practice to keep active branches seperated to be merged into master later.
    - I'd recommed creating your own branch, then get a checkout of it. I'll handle firmware merges compiling all of the features into the master branch.
2. [Commits](https://www.atlassian.com/git/tutorials/saving-changes/git-commit)
    - Something akin to saving your progress, a commit is what you do when you've reached some sort of milestone. You can commit specific files if you'd like, but typically you'll be pressing the "**stage** all" button and then writing a small update message when you commit.
    - **Staging** is when you specify which files are going into a single commit. Like I said earlier, you probably just want to stage all at our level. Larger projects like to keep changes as atomic as possible though.
3. [Fetching](https://www.atlassian.com/git/tutorials/syncing/git-fetch)
    - While many people go for the hard pull, I'd recommend fetching and then merging. This is primarily for 2 reasons;
      A. You don't lose your work if someone has updated just a small amount of code in your branch by accident.
      B. You can see the little changes and ignore them if you'd like. Merging can get buggy, getting a feature done sooner and debugging later is more optimized.
4. [Pushing](https://www.atlassian.com/git/tutorials/syncing/git-push)
    - How you upload all of your local commits to the cloud. This will push to the branch you've checked out only, but it can be rolled back using some advanced commands.
    - Don't panic if you accidentally upload to Master! History can be rewritten and redirected, just shoot me a text and I'll take care of it.

## PlatformIO Libraries
These libraries are required installations on everyone's platformIOs. I would like to mitigate the need for this later, as it should be possible to leverage the /lib folder, but for now follow the following instructions:
- Navigate to PIO Home.
- Select Libraries on the left.
- Search the registry.
- Select the proper library and click "Add to Project"
- Double check platformio.ini that all libraries follow the format Author/Library @ ^vX.X.X

### Library List
1. TMCStepper
2. ArduinoJSON