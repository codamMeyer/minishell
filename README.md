- [Minishell Project - Tutorial](#minishell-project---tutorial)
    - [How to work as a team](#how-to-work-as-a-team)
    - [What's Continuous Integration (CI) ?](#whats-continuous-integration-ci-)
    - [How to setup CircleCI Tool ?](#how-to-setup-circleci-tool-)

# Minishell Project - Tutorial
### How to work as a team


### What's Continuous Integration (CI) ?

![ci_flow](/images/ci_flow.png)

It is the practice of integrating changes from different developers in the team into a mainline as early as possible, in best cases several times a day. This makes sure the code individual developers work on doesn’t divert too much. When you combine the process with automated testing, continuous integration can enable your code to be dependable.

### How to setup CircleCI Tool ?

![ci_flow](/images/circleci/1.png)

1. In the root of your directory, run:
    ```bash
    mkdir .circleci
    cd .circleci
    touch config.yml
    ```
2. Copy the example bellow in your config.yml file:
    ```yaml
    version: 2

    jobs:
      build:
        docker:
          - image: "debian:buster"
        steps:
          - checkout
          - run:
              name: Install dependencies
              command: 'apt-get update && apt-get install -y gcc make python3 python3-pip'
          - run:
              name: Install dependencies Python
              command: 'pip3 install -U pip && pip3 install -U setuptools && pip3 install -U norminette'
          - run:
              name: Build
              command: 'echo Building'
          - run:
              name: Unit-Test
              command: "echo Unit-Test"
          - run:
              name: Integration-Test
              command: "echo Integration-Test"
          - run:
              name: Norminette Check
              command: "echo run norminette"
    ```

Access [**circleci**](https://circleci.com/signup/) and sign up with your **github** account.
Click on **Projects**
Click on **Set Up project**
