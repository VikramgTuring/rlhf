
class Target {
public:
    virtual void operation(int arg) = 0;
};


template<typename TargetT, typename ArgT>
class Command {
public:
    virtual ~Command() = default;

    virtual void execute(TargetT* target, ArgT arg) = 0;

protected:
    TargetT* target_;
    ArgT arg_;
};


template<typename TargetT>
class ConcreteCommand : public Command<TargetT, int> {
public:
    ConcreteCommand(TargetT* target, int arg) : target_(target), arg_(arg) {}

    void execute(TargetT* target, int arg) override {
        target->operation(arg);
    }
};


class Invoker {
public:
    template<typename TargetT>
    void setCommand(std::unique_ptr<Command<TargetT, int>> command) {
        command_ = std::move(command);
    }

    void invoke() {
        command_->execute(nullptr, 0); // The target and argument are handled in the concrete command
    }

private:
    std::unique_ptr<Command<TargetT, int>> command_;
};


class ConcreteTarget : public Target {
public:
    void operation(int arg) override {
        std::cout << "ConcreteTarget::operation(" << arg << ")" << std::endl;
    }
};

int main() {
    ConcreteTarget target;
    Invoker invoker;

    // Create and set a command
    invoker.setCommand(std::make_unique<ConcreteCommand<ConcreteTarget>>(&target, 10));

    // Invoke the command
    invoker.invoke();

    return 0;
}

