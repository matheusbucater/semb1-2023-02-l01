# Ferramentas da toolchain

## C Compiler
CC = arm-none-eabi-gcc

## Remove files
RM = rm -rf

# Diretórios

## Arquivos objeto
OBJDIR = build

## Lista de dependências
DEPDIR = .deps

# Arquivos que serão compilados

SRCS = src/startup.c src/main.c

# Flags do Compilador

## Compilação
CFLAGS = -g -mcpu=cortex-m4 -mthumb -Wall -O0

## Geração de dependências
DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d

# Arquivos objeto

## Lista de arquivos objeto
OBJS = $(patsubst %, $(OBJDIR)/%.o, $(basename $(SRCS)))

## Criação do diretório de arquivos objeto
$(shell mkdir -p $(dir $(OBJS)) > /dev/null)

# Arquivos de dependência

## Lista de dependências
DEPS = $(patsubst %, $(DEPDIR)/%.d, $(basename $(SRCS)))

## Criação do diretório de dependências
$(shell mkdir -p $(dir $(DEPS)) > /dev/null)

all: $(OBJS)

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

$(DEPS): 

-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(DEPDIR)
