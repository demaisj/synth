SRCDIR		:=	src
INCDIR		:=	src include
BUILDDIR	:=	build

RM		:=	rm -f
RMDIR		:=	rm -rf
MKDIR		:=	mkdir -p

CXX		:=	g++ -pthread
CXXFLAGS	:=	-std=c++17 -Ofast
#CXXFLAGS	+=	-Wall -Wextra
CXXFLAGS	+=	-g3
CPPFLAGS	:=	$(addprefix -I, $(INCDIR)) -MD

NAME		:=	synth
SRCS		:=	$(addprefix $(SRCDIR)/, \
			main.cpp \
			Synth.cpp \
			MIDI/Reciever.cpp \
			MIDI/Message.cpp \
			MIDI/Tuner.cpp \
			Modules/Core/PulseOutput.cpp \
			Modules/Core/VoiceManager.cpp \
			Modules/Core/Voice.cpp \
			Modules/Generators/Oscillator.cpp \
			Modules/Envelopes/Envelope.cpp \
			Modules/Effects/Delay.cpp \
			Modules/Effects/Filter.cpp \
			)
OBJS		:=	$(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(patsubst %.cpp, %.o, $(SRCS)))
DEPS		:=	$(patsubst %.o, %.d, $(OBJS))
LDFLAGS		:=	$(addprefix -l, \
			m \
			pulse \
			pulse-simple \
			)


all:			$(NAME)

$(NAME):		$(OBJS)
			@echo "LINK $@"
			@$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o:	$(SRCDIR)/%.cpp
			@$(MKDIR) $(dir $@)
			@echo "CXX $<"
			@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
			@echo "RM OBJS"
			@$(RM) $(OBJS)
			@echo "RM DEPS"
			@$(RM) $(DEPS)

fclean:			clean
			@echo "RMDIR $(BUILDDIR)"
			@$(RMDIR) $(BUILDDIR)
			@echo "RM $(NAME)"
			@$(RM) $(NAME)

re: 			fclean all

-include 		$(DEPS)

.PHONY:			all clean fclean re
