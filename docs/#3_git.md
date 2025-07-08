# Best Practices for Branch Usage

Using branches properly helps keep your code organized, makes collaboration easier, and helps avoid conflicts.

---

## How to Create and Manage a New Branch

### Create and switch to a new branch
Use the command:

```
git checkout -b <branch-name>
```

This command creates and switches to a new branch where you can work without affecting the main branch.

Use -b only when creating a new branch. To switch between existing branches, just use checkout.

## Update main Before Finalizing Your Work

Before wrapping up your task, make sure the main branch is up to date with the remote repository:
```
git checkout main
```
```
git pull origin main
```
Why?
Because we need to merge main into your working branch to ensure you're working with the latest version.

## Update Your Branch with the Latest Version of main
```
git checkout <sua branch>
```
```
git merge main
```

Now, just push your branch:
```
git push -u origin <sua branch>
```

Note: Use -u only the first time you push the branch.

Done! Your task has now been pushed and is ready for review by the team.

## After Review, Merge Your Branch into main
```
git checkout main
```
```
git merge <sua-branch>
```
```
git push origin main
```

And that’s it — main is now updated with the new changes.

# Workflow Simulation

---

### 1.  Update main

`git checkout main`

`git pull origin main`

### 2. Create your branch

`git checkout -b parser`

### 3. Work on your core

`echo "New feature" > new_feature.txt`

### 4. add and commit

`git add .`

`git commit -m "feat: add new feature"`

_(Repeat as many commits as needed during development)_

### 5. Update main

`git checkout main`

`git pull origin main`

### 6.  Merge main into your branch

`git checkout parser`

`git merge main`

**If there are conflicts,** resolve them manually, then:

`git add .`

`git commit`

### 7.  Push your branch to GitHub for review

`git push -u origin parser`

### 8. After review and approval, switch back to main and merge

`git checkout main`

`git merge parser`

### 9. Push the updated main to the remote repository

`git push origin main`